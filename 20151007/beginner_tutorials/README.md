1-1, makeはMakefileに書かれた依存関係に則ってコンパイルするのに対し、catkin_makeでは独立してコンパイルが行われる。

1-2, catkin_makeにおいてはCmakeのルールに従ってコンパイルするから。

1-3, ros::Spin()はクローズまでros::SpinOnce()を呼び出す関数である。

1-4, msgファイルが生成される。

3, topic: motor_power, cmd_vel
   message: linear_vel_step, linear_vel_max, angular_vel_step, angular_vel_max, wit_for_connection

