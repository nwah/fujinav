   .export _callciov
   .export _channel
   .export _result
ciov=$e456

    .proc _callciov: near
    .code
_callciov:
    lda _channel
    clc
    rol a   ; channel * 16
    rol a
    rol a
    rol a
    tax
    jsr ciov
    sty _result

    rts
    .endproc
_channel: .byte 0
_result: .byte 0
