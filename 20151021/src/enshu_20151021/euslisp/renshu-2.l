#!/usr/bin/env irteusgl

(load "lib/llib/unittest.l")
(init-unit-test)
(send *unit-test* :clear-result)
;; DO NOT EDIT BEFORE THIS LINE

;; 2)
;; サーボモジュールを参考に直動ジョイント(linear-joint)を使ったアクチュエータを作ってみよ．
(defun make-servo nil
  (let (b1 b2)
    (setq b1 (make-cube 35 20 46))
    (send b1 :locate #f(9.5 0 0))
;    (setq b2 (make-cylinder 3 60))
 ;   (send b2 :locate #f(0 0 -30))
  ;  (setq b1 (body+ b1 b2))
    (send b1 :set-color :red)
    b1))

(defun make-hinji nil
  (let ((b2 (make-cube 50 50 100))
	(b1 (make-cube 50 20 99)))
    (send b2 :locate #f(-4 0 0))
    (setq b2 (body- b2 b1))
    (send b2 :set-color :white)
    b2))

(setq h1 (instance bodyset-link :init (make-cascoords) :bodies (list (make-hinji))))
(setq s1 (instance bodyset-link :init (make-cascoords) :bodies (list (make-servo))))
(setq j1 (instance linear-joint :init :parent-link h1 :child-link s1 :axis :z))

(setq r (instance cascaded-link :init))
(send r :assoc h1)
(send h1 :assoc s1)
(setq (r . links) (list h1 s1))
(setq (r . joint-list) (list j1))
(send r :init-ending)

(objects (list r))

(dotimes (i 400)
  (send r :angle-vector (float-vector (* 20 (sin (/ i 10)))))
  (send *irtviewer* :draw-objects))


;; DO NOT EDIT AFTER THIS LINE
(send *unit-test* :print-result)
(exit 1)




