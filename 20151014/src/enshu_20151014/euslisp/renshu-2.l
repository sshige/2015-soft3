#!/usr/bin/env irteusgl

(load "lib/llib/unittest.l")
(init-unit-test)
(send *unit-test* :clear-result)
;; DO NOT EDIT BEFORE THIS LINE


;; 1
(defun dot-1 (n)
  (dotimes (i n)
    (format t ".")
)
t)  


(defun dot-2 (n)
  (if (eq n 0)
      nil
      (progn (format t ".") 
             (dot-2 (- n 1))))
t)

;; 
(assert (dot-1 3) "mondai 1")
(assert (dot-2 3) "mondai 1")

;; 2
(defun hasa-1 (lst)
  (let (res)
    (setq res 0)
    (dolist (i lst)
      (when (equal i 'a)
        (setq res (+ res 1))))
    res))

(defun hasa-2 (lst)
  (hasa-22 0 lst)
)
(defun hasa-22 (i lst)
  (if (equal lst nil)
	i
    (progn (if (equal 'a (car lst))
               (hasa-22 (+ i 1) (cdr lst))
               (hasa-22 i (cdr lst)))))))
;; 
(assert (eq (hasa-1 '(a b c d a)) 2) "mondai 2")
(assert (eq (hasa-2 '(a b c d a)) 2) "mondai 2")

;; DO NOT EDIT AFTER THIS LINE
(send *unit-test* :print-result)
(exit 1)




