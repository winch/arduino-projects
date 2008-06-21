#!/usr/bin/ruby -w

require 'serialport.so'

if ARGV.size < 1
    puts 'Usage ./controller.rb serialPort'
    exit
end

sp = SerialPort.new(ARGV[0].to_i, 9600, 8, 1, SerialPort::NONE)

sp.putc('a')
sleep(5)
sp.putc('b')
sleep(1)
sp.putc('r')
sleep(1)
sp.putc('b')
sleep(5)
sp.putc('r')

sp.close

