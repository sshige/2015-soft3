#!/usr/bin/env irteusgl

(load "lib/llib/unittest.l")
(init-unit-test)
(send *unit-test* :clear-result)
;; DO NOT EDIT BEFORE THIS LINE

;; 3)
;; ascaded-linkを使ったモデルを作成せよ．ロボットに限らず可動構造を持つものであれば（例えば家具等）何でもよい．
(defclass ritual
  :super cascaded-link
  :slots (base sphere joint1 joint2 joint3 joint4 joint5 joint6))

(defmethod ritual
  (:init 
   ()
   (let (h1 h2 h3 h4)
     (send-super :init)

     (setq base (make-cylinder 40 10))
     (setq sphere (make-sphere 10))
  
     (setq h1 (make-cylinder 5 25))
     (setq h2 (make-cylinder 5 25))
     (setq h3 (make-cylinder 5 25))
     (setq h4 (make-cylinder 5 25))
     
     (send self :assoc base)
     (send base :assoc sphere)
     (send base :assoc h1)
     (send base :assoc h2)
     (send base :assoc h3)
     (send base :assoc h4)

     (send sphere :locate #f(0 0 5))
     
     (send h1 :locate #f(30 0 5))
     (send h2 :locate #f(-30 0 5))
     (send h3 :locate #f(0 30 5))
     (send h4 :locate #f(0 -30 5))

     (send sphere :set-color :gray20)
     (send base :set-color :white)
     
     (send h1 :set-color :red)
     (send h2 :set-color :red)
     (send h3 :set-color :red)
     (send h4 :set-color :red)
     
     (setq joint1 (instance linear-joint :init :parent-link base :child-link sphere :axis :z))
     (setq joint3 (instance linear-joint :init :parent-link base :child-link h1 :axis :z))
     (setq joint4 (instance linear-joint :init :parent-link base :child-link h2 :axis :z))
     (setq joint5 (instance linear-joint :init :parent-link base :child-link h3 :axis :z))
     (setq joint6 (instance linear-joint :init :parent-link base :child-link h4 :axis :z))

     (objects (list base sphere h1 h2 h3 h4))
     ))

  (:start
   (n)
   (dotimes (i n)
     (send joint1 :joint-angle (* 10 (/ i 50.0)))
     (send joint3 :joint-angle (* 5 (sin (/ i 50.0))))
     (send joint4 :joint-angle (* 4 (sin (/ i 50.0))))
     (send joint5 :joint-angle (* 3 (sin (/ i 50.0))))
     (send joint6 :joint-angle (* 2 (sin (/ i 50.0))))
     (send base :rotate (deg2rad 1) :z)
     (send *irtviewer* :draw-objects)
     (x::window-main-one))))
 
(defun ritual nil
  (let (r)
    (setq r (instance ritual :init))
    (send r :start 300)))

(ritual)

;; DO NOT EDIT AFTER THIS LINE
(send *unit-test* :print-result)
(exit 1)




