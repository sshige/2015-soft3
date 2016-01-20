#!/usr/bin/env roseus
;;;
;;; euslisp version of ros_tutorials/rospy_tutorials/005_add_two_ints
;;;
(ros::load-ros-manifest "roseus")

;;;
(ros::roseus "add_two_ints_server")

(defclass string-cb-class
  :super
  :slots ())
(defmethod string-cb-class
  (:init () (ros::subscribe "chatter" std_msgs::String #'send self :string-cb))
  (string-cb (msg) (let ((m (send req :response)))
		     (format *error-output* "Returning [~d + ~d = ~d]~%"
			     (send req :a) (send req :b)
			     (+ (send req :a) (send req :b)))
		     (send m :sum  (+ (send req :a) (send req :b)))
		     m)))
(setq m (instance string-cb-class :init))
;;;
;;;

(do-until-key
 (ros::spin-once))




