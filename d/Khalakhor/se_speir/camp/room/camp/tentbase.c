inherit "/std/room";

void
create_room()
{
  ::create_room();
  
  set_short("In one of the many clan Baran war tents");
  
  set_long("You stand inside of a great war tent. Weapons, "
      +"shields, and battle plans are strewn about the tent. "
	  +"Here, Warriors bunk and rest for upcoming conflicts. "
	  +"The tent smells absolutely awful, there are cards and "
	  +" drinks littered at your feet.\n");
  
  add_item(({"tent","bunk","great war tent", "room"}),
     "The tent you are standing in smells horrendous and disorderly "
	  +"you can make out the peaks of great mountains. To "
      +"the west, you can see countless trees, fading into "
	  +"the distance, around you the forest seems to be alive: "
      +"emitting natural sounds and a general relaxing atmosphere.\n");
	 
  add_item(({"swords","shields","battle plans","cards"}),
	  "The tent is coated in dirt, along the bunks and on tables there "
     +"are knives, sketches of Port Macdunn and invasion routes. There "
	 +"are also cards which the soldiers use to pass the time.\n");
	   
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
