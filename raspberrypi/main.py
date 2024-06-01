# 動作未確認
import simpleaudio as sa
import serial
import time
import sys

if len(sys.argv) != 3:
    print(f'Usage: python {sys.argv[0]} [path/to/wave/file] [path/to/serial/device]')
    sys.exit(1)


wave_obj = sa.WaveObject.from_wave_file(sys.argv[1])
ser = serial.Serial(sys.argv[2], 9600)

play_obj = None

buff = ''
sleep = False

try:
    while True:
        if sleep and play_obj == None:
            print(f'play audio: {sys.argv[1]}')
            play_obj = wave_obj.play()

            # waiting for 'awake!'
            print('waiting for awake')
            while ser.in_waiting == 0:
                time.sleep(0.1)

            buff = ser.readline().strip()
            if buff == b'awake!':
                print('awake detected!')
                sleep = False
                # if play_obj.is_playing():
                    # play_obj.stop()
                play_obj = None
            else:
                print('awake not detected')
        else:
            # waiting for 'sleep!'
            if ser.in_waiting != 0:
                buff = ser.readline().strip()
                if buff == b'sleep!':
                    print('sleep detected!')
                    sleep = True
                pass
            else:
                time.sleep(0.1)

except KeyboardInterrupt:
    if play_obj != None:
        play_obj.wait_stop()

    ser.close()

