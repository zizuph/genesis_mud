inherit "/std/room";

void
create_room()
{
  ::create_room();
  set_short("on a faded path in the wild forest, east of Port Macdunn");
  set_long("You stand on a faded trail, leading to the east and west. The path lies "
	  +"east of Port Macdunn, yet the landscape looks completely different to "
	  +"that of Port Macdunn's. The forest is alive with wildlife, and you hear "
	  +"only the sounds of nature and the environment around you. A very soothing "
	  +"atmosphere overtakes you as Port Macdunn fades to the background. Overhead, "
	  +"the sky is light blue, spotted with idle clouds floating by.\n");
  add_item(({"forest","wild","landscape", "atmosphere"}),
     "The forest surrounds you completely. To the north, "
	  +"you can make out the peaks of great mountains. To "
    +"the west, you can see countless trees, fading into "
	  +"the distance, around you the forest seems to be alive: "
    +"emitting natural sounds and a general relaxing atmosphere.\n");
  add_item(({"port macdunn"}),
      "The town is beginning to fade in the distance, " +
      "becoming only a distant scene to the east.\n");
  add_item(({"trail","rough trail","path"}),
      "It is merely a worn, simple "
     +"dirt path, nothing much to note.\n");
  add_item(({"wildlife","sounds"}),
	  "The forest seems to be surrounding you totally and utterly. "
     +"Around you, are colourful birds on branches and squirrels "
	 +"darting through the underbrush.\n");
 add_item(({"sky","clouds"}),
	  "Looking upwards, the sky appears to be as calming as the forest "
	 +"around you currently. Idle clouds float bye.\n");
	   
}

void
summon_kguard()
{
    setuid();
    seteuid(getuid());
    
    object guard;
    
    guard = clone_object("/w/stark/celtcamp/kguard.c");
    guard->move(this_object());
}
