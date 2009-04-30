#!/usr/bin/ruby -w

require 'serialport'
require 'joystick'
require File.dirname(__FILE__) + '/axis.rb'

if ARGV.size < 2
    puts 'Usage ./controller.rb serialPort joystick'
    exit
end

LEFT_AXIS = 1
RIGHT_AXIS = 2

sp = SerialPort.new(ARGV[0], 9600, 8, 1, SerialPort::NONE)
js = Joystick::Device::open ARGV[1]

left = Axis.new('l', sp, 0, -255, 255, true)
right = Axis.new('r', sp, 0, -255, 255, true)

go = true
while go == true
    event = js.next_event
    
    case event.type
    when Joystick::Event::BUTTON
        go = false if event.num == 0 && event.val == 1
    when Joystick::Event::AXIS
        if event.num == LEFT_AXIS
            left.update(event.val)
        end
        if event.num == RIGHT_AXIS
            right.update(event.val)
        end
    end
end

sp.close
js.close

