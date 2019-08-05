break BSP_CAMERA_SnapshotStart
commands 
    silent
    next
    shell sleep 1
    set $start=data
    set $end=$start + 0x2580
    dump mem file.jpg $start $end
end
