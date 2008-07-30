#!/usr/bin/ruby -w

require 'serialport'
require File.dirname(__FILE__) + '/methods.rb'

if ARGV.size < 1
    puts 'Usage remote.rb serialPort'
    exit
end

sp = SerialPort.new(ARGV[0], 9600, 8, 1, SerialPort::NONE)
sp.read_timeout = 2


input = ''

while input != 'q'

    input = STDIN.gets.chomp

    case input
    when 'q'
        #quit
        sp.close
        exit
    when 's'
        #send time
        input = 's' + TimeMethods.get_time_string()
    end
    
    puts "Sending " + input
    input.each_byte do |char|
        print "#{char} "
        sp.putc(char)
    end
    print "\n"
    sleep 0.5
    
    puts sp.gets
    
end

sp.close

