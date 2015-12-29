#!/usr/bin/env eusgl

(setq m (load-foreign "./ffi-c.so"))
(defforeign sinc m "sinc" (:float) :float)
(defforeign hello m "hello" (:string) :integer)
(format t "sinc=~A~%" (sinc 1.0))
(format t "hello ")(finish-output t)
(hello "world")
(exit)

