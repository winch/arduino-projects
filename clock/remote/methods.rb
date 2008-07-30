
module TimeMethods

    #return a string containing the time in a format expected by the clock
    # YYMMDDHHMMSSa/p
    def TimeMethods.get_time_string
        Time.now.strftime('%y%m%d%w%I%M%S%P').downcase.chomp('m')
    end
    

end
