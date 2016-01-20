#!/usr/bin/env irteusgl

(load "lib/llib/unittest.l")
(init-unit-test)
(send *unit-test* :clear-result)
;; DO NOT EDIT BEFORE THIS LINE

;; 6)
;; ロボットや環境のモデルファイルを利用して，日常生活空間で作業するロボットのプログラムを書いてみよ．

(load "models/room73b2-scene.l")
(load "models/h7-robot.l")
(setq *room* (room73b2))
(setq *robot* (h7))
(objects (list *robot* *room*))

(send *robot* :reset-pose)

(send *robot* :move-to (send *room* :spot "cook-spot") :world)
(send *robot* :locate #f(0 100 550))

(send *irtviewer* :look-all
      (geo::make-bounding-box
       (flatten (send-all (send *robot* :bodies) :vertices))))

(setq *kettle* (send *room* :object "room73b2-kettle"))
(if (send *kettle* :parent) (send (send *kettle* :parent) :dissoc *kettle*))
(send *robot* :head :look-at (send *kettle* :worldpos))

(send *robot* :larm :inverse-kinematics
      (car (send *kettle* :handle))
      :link-list (send *robot* :link-list (send *robot* :larm :end-coords :parent))
      :move-target (send *robot* :larm :end-coords)
      :rotation-axis :z
      :debug-view t)  
(send *robot* :larm :end-coords :assoc *kettle*)
(send *robot* :larm :move-end-pos #f(0 0 300) :world
      :debug-view t :look-at-target t)
(send *robot* :larm :move-end-pos #f(0 0 0) :world
      :debug-view t :look-at-target t)
(send *robot* :larm :move-end-pos #f(0 0 300) :world
      :debug-view t :look-at-target t)
(send *robot* :larm :move-end-pos #f(0 0 0) :world
      :debug-view t :look-at-target t)



;; DO NOT EDIT AFTER THIS LINE
(send *unit-test* :print-result)
(exit 1)





