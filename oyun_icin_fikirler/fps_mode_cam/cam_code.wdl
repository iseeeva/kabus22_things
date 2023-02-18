var start4_cam_no=1;
var zeksen=0;
var screenocam;
var distance_temp=0;
action start4_camera // attach it to fish.mdl, etc
{
	my.passable=on;
	my.invisible=on;
	camera.size_x = screen_size.x;
	camera.size_y = screen_size.y;
	camera.pos_x = 0;
	camera.pos_y = 0;
	camera.arc=62;
	camera.visible=on;
	while(1)
	{
		
	screenocam=file_open_read("k22_cam.cfg");
	if(screenocam!=0)
	{
		dist_total=file_var_read(screenocam);
		distance_temp=file_var_read(screenocam);
		tilt_3rd=file_var_read(screenocam);
		yuksek=file_var_read(screenocam);
		zeksen=file_var_read(screenocam);
		camera.arc=file_var_read(screenocam);
		file_close(screenocam);
	}
		
		if(player!=null)
		{
			if(aktif_player==0){ //demir
				
			if (aktif_silah==3){ // m4a1
			if (Key_Ileri==0){ //idle
				dist_total=2;
				camera.tilt = clamp(camera.tilt,-45,40);				
			}else{ //yürü
				dist_total=1;
				camera.tilt = clamp(camera.tilt,-30,40);				
			}
		    if (Key_SilahKaldir==1){ //nişan al
				yuksek-=distance_temp;
				dist_total=7;
				camera.tilt = clamp(camera.tilt,-5,40);
			}
			if (Key_Kosma==1){ //koş
				dist_total=1;
				camera.tilt = clamp(camera.tilt,-25,40);				
			}}
			
			if (aktif_silah==1){ //tabanca
			if (Key_Ileri==0){ //idle
				dist_total=8;
				camera.tilt = clamp(camera.tilt,-25,40);				
			}else{ //yürü
				dist_total=8;
				camera.tilt = clamp(camera.tilt,-14,40);				
			}
		    if (Key_SilahKaldir==1){ //nişan al
				yuksek-=distance_temp;
				dist_total=6;
				camera.tilt = clamp(camera.tilt,-5,40);
			}
			if (Key_Kosma==1){ //koş
				dist_total=5;
				camera.tilt = clamp(camera.tilt,-10,40);				
			}}
			
			}
			
			dist_planar = cos (tilt_3rd) * dist_total;
			camera.x=player.x-cos(player.pan)*dist_planar;
			camera.y=player.y -zeksen- sin(player.pan)*dist_planar;
			camera.z=player.z +yuksek+ sin (tilt_3rd) * dist_planar;
			player.pan -= 8 * mouse_force.x * time;
			camera.pan	=player.pan;
			camera.roll=0;
			camera.tilt += 8 * mouse_force.y * time;
			validate_view();

				if(bombacam_salla_s==on)
				{
					camera.pan+=bombacam_salla_m*(random(10)-5);
					camera.tilt+=bombacam_salla_m*(random(10)-5);
				}
				
		}
		wait(1);
	}
}