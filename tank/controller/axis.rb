
class Axis
    
    def initialize(ident, serial, centre, min, max, reverse)
        @ident = ident
        @sp = serial
        @output_centre = centre
        @output_min = min
        @output_max = max
        @output_range = max - min
        @min = 0
        @max = 0
        @current = 0
        @diff = 100
        @reverse = reverse
    end
    
    car = 1000
    joy = 500
    
    #update the axis if required
    def update(value)
        value = value * -1 if @reverse == true
        @max = value if value > @max
        @min = value if value < @min
        
        if (@current - value).abs > @diff
            @current = value
            send
        end
    end
    
    #send value over serial port
    def send
        if @sp.nil? == false
            range = @max - @min
            scale = @output_range / range.to_f
            value = (@current * scale) + @output_centre
            value = @output_max if value > @output_max
            value = @output_min if value < @output_min
            value = value.to_i.to_s
            
            #send over serial
            @sp.putc(@ident)
            value.each_byte do |char|
                @sp.putc(char)
            end
            @sp.putc('e')
            #puts "sent #{@ident}#{value}"
        end
    end
    
end

