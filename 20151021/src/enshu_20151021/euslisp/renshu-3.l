#!/usr/bin/env irteusgl

(load "lib/llib/unittest.l")
(init-unit-test)
(send *unit-test* :clear-result)
;; DO NOT EDIT BEFORE THIS LINE

;; 3)
;; ascaded-linkを使ったモデルを作成せよ．ロボットに限らず可動構造を持つものであれば（例えば家具等）何でもよい．

(defclass cascaded-link
  :super cascaded-coords
  :slots (links joint-list bodies collision-avoidance-links))

(defmethod cascaded-link
  (:init (&rest args &key name &allow-other-keys)
	 (send-super-lexpr :init args)
	 self)
  (:init-ending
   ()
   (setq bodies (flatten (send-all links :bodies)))
   (dolist (j joint-list)
     (send (send j :child-link) :add-joint j)
     (send (send j :child-link) :add-parent-link (send j :parent-link))
     (send (send j :parent-link) :add-child-links (send j :child-link)))
   (send self :update-descendants))
)

(defun make-servo nil
  (let (b1 b2)
    (setq b1 (make-sphere 20))
    (send b1 :locate #f(0 0 0))
    (send b1 :set-color :red)
 ;   (send b2 (make-cube 50 50 5))
  ;  (send b2 :locate #f(9.5 0 20))
   ; (send b2 :set-color :red) 
;    (setq b2 (make-cylinder 3 60))
 ;   (send b2 :locate #f(0 0 -30))
   ; (setq b1 (body+ b1 b2))
    b1))

(defun make-hinji nil
  (let ((b2 (make-cube 50 50 20))
	(b1 (make-cube 26 24 24)))
    (send b2 :locate #f(0 0 -20))
;    (setq b2 (body- b2 b1))
    (send b2 :set-color :white)
    b2))

(defclass servo-model
  :super cascaded-link
  :slots (h1 s1 j1))
(defmethod servo-model
  (:init ()
   (let ()
      (send-super :init)
      (setq h1 (instance bodyset-link :init (make-cascoords) :bodies (list (make-hinji))))
      (setq s1 (instance bodyset-link :init (make-cascoords) :bodies (list (make-servo))))

      (setq j1 (instance linear-joint :init :parent-link h1 :child-link s1 :axis :x))

      (setq links (list h1 s1))
      (setq joint-list (list j1))

      (send self :assoc h1)
      (send h1 :assoc s1)

      (send self :init-ending)
      self))
;  (send r :j1 :joint-angle 30)
  (:j1 (&rest args) (forward-message-to j1 args))
)

(setq r (instance servo-model :init))

(objects (list r)) 
(dotimes (i 300)
  (send r :angle-vector (float-vector (* 10 (sin (* 90 (/ i 500.0))))))
  (send *irtviewer* :draw-objects))

;; DO NOT EDIT AFTER THIS LINE
(send *unit-test* :print-result)
(exit 1)






