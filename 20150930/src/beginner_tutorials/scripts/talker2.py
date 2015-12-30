#!/usr/bin/env python
import roslib
import rospy
from std_msgs.msg import String
<<<<<<< HEAD
from beginner_tutorials.msg import Hello

def talker2():
	pub = rospy.Publisher('chatter2',Hello)
	rospy.init_node('talker')
	while not rospy.is_shutdown():
		str = "hello world %s"%rospy.get_time()
		rospy.loginfo(str)
		hello = Hello();
		hello.hello = "world"
		hello.pos.x = 0;
		hello.pos.y = 1;
		hello.pos.z = 2;
		pub.publish(hello);
		rospy.sleep(1.0)
if __name__ == '__main__':
	try:
		talker2()
	except rospy.ROSInterruptException: pass
=======
from beginner_tutorials.msgs import Hello

def talker():
    pub = rospy.Publisher('chatter2',String)
    rospy.init_node('talker')
    while not rospy.is_shutdown():
        str = "hello world %s"%rospy.get_time()
        rospy.loginfo(str)
        hello = Hello();
        hello.hello = "world"
        hello.pos.x = 0;
        hello.pos.y = 1;
        hello.pos.z = 2;
        pub.publish(hello)
        rospy.sleep(1.0)
if __name__ == '__main__':
    try:
        talker2()
    except rospy.ROSInterruptException: pass
>>>>>>> f5cb1c287b2c6b3c296cb4a319bcf6c4e661da94
