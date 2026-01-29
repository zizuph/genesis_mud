inherit "/d/Gondor/common/room";

create_room() 
{
  set_short("The private office of Councellor Olorin");
  set_long("It's a private office. Private! You know what that means?\n");
  add_exit("/d/Gondor/olorin/battle_test","battle",0,0);
}

