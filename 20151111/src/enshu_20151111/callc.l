(setq m (load-foreign "./callc.so"))

(defforeign setlfunc m "setlfunc" (:integer) :integer)
(defforeign callfunc m "callfunc" (:integer) :integer)

(defun-c-callable TEST ((a :integer)) :integer
  (format t "TEST is called, arg is ~A~%" a)
  (* a a))

(setlfunc (pod-address (intern "TEST")))
(callfunc 12)
(exit)
