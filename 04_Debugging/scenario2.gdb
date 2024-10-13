set pagination off
set $print_point = -1
b 32
commands
    silent
    set $print_point = $print_point + 1
    
    if $print_point >= 28 && $print_point <= 35
        echo @@@
        p start
        echo @@@
        p end
        echo @@@
        p step
        echo @@@
        p i
    end
    cont
end

run
quit