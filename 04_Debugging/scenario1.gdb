set pagination off
b 32 if i % 5 == 0
command 1
    silent
    
    echo @@@
    p start
    echo @@@
    p end
    echo @@@
    p step
    echo @@@
    p i
    cont
end

run
quit