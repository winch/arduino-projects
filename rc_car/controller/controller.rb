#!/usr/bin/ruby -w

require 'serialport'
require 'joystick'
require File.dirname(__FILE__) + '/axis.rb'

if ARGV.size < 1
    puts 'Usage ./controller.rb serialPort joystick'
    exit
end

STEER_AXIS = 0
THROTTLE_AXIS = 2


sp = SerialPort.new(ARGV[0], 9600, 8, 1, SerialPort::NONE)
js = Joystick::Device::open ARGV[1]

throttle = Axis.new('t', sp, 1500, 1000, 2000, true)
steer = Axis.new('s', sp, 1500, 1240, 1860, false)

go = true
while go == true
    event = js.next_event
    
    case event.type
    when Joystick::Event::BUTTON
        go = false if event.num == 0 && event.val == 1
    when Joystick::Event::AXIS
        if event.num == STEER_AXIS
            steer.update(event.val)
        end
        if event.num == THROTTLE_AXIS
            throttle.update(event.val)
        end
    end
end

sp.close
js.close

