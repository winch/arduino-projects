#!/usr/bin/ruby -w

require 'serialport'

if ARGV.size < 1
    puts 'Usage remote.rb serialPort'
    exit
end

sp = SerialPort.new(ARGV[0], 9600, 8, 1, SerialPort::NONE)
sp.read_timeout = 2


input = ''

while input != 'q'

    input = STDIN.gets.chomp

    print "Sending "
    input.each_byte do |char|
        print "#{char} "
        sp.putc(char)
    end
    print "\n"
    sleep 0.25
    
    puts sp.gets
    
    
    
end

sp.close

