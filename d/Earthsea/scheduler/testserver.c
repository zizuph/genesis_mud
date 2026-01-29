inherit "/std/room";

#define DEBUG(x) find_player("ged")->catch_msg(x+"\n")

int allowed=0;
int delayed=0;

void create_room()
{
 set_short("Test server");
 set_long("This is a test server for custom events scheduler.\n");
}

void allow() {allowed=1;}
void disallow() {allowed=0;}
int is_allowed() {return allowed;}

void delay() {delayed=1;}
void undelay() {delayed=0;}
int is_delayed() {return delayed;}

float go()
{
 if(!allowed) return -1.0;
 if(delayed)
  {
   DEBUG("Delayed the launch");
   return 10.0;
  }

 return 0.0;
}

