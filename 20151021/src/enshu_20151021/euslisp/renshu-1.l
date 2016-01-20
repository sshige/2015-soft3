#!/usr/bin/env irteusgl

(load "lib/llib/unittest.l")
(init-unit-test)
(send *unit-test* :clear-result)
;; DO NOT EDIT BEFORE THIS LINE

;; 1)
;; 太陽，地球，月のモデルをつくり，太陽の周りを地球が，地球の周りを月が回っているアニメーションを作成せよ
(setq c1 (make-sphere 100))
(setq c2 (make-sphere 50))
(setq c3 (make-sphere 10))
(send c1 :set-color :red)
(send c2 :set-color :blue)
(send c3 :set-color :yellow)
(send c2 :locate #f(300 0 0))
(send c3 :locate #f(400 0 0))
(send c1 :assoc c2)
(send c2 :assoc c3)
(objects (list c1 c2 c3))
(do-until-key
 (send c1 :rotate (deg2rad 5) :z)
 (send c2 :rotate (deg2rad 100) :z)
 (send *irtviewer* :draw-objects)
 (x::window-main-one)
)



;; DO NOT EDIT AFTER THIS LINE
(send *unit-test* :print-result)
(exit 1)



