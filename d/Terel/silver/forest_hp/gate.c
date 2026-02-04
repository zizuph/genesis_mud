/* Treasure room in silver forest,
 by Udana 03/2006,
 original code done for Krynn, by same author, 01/2006
 */


#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>
#include "/d/Terel/include/Terel.h"
#include "../include/defs.h"
#include <composite.h>

#define PLAYER_I_SOLVED_DEC_Q "_player_i_solved_dec_q"

inherit INCLUDE + "forest_base";

int knocked = 0;
int opened = 0;
/* To save players time and effort I made password and key rather small
   it creates possibility of guessing it by flooding with random strings of
   correct length. Flag 'tried' will be up for few seconds after each 'say'
   command, and will block all further attempts.*/
int tried = 0;
/* returns 1 if sender read both password and decryption key, and if what was 'said'
   is decrypted password. */
int decrypt(object sender, string said);
void remove_flag();

void reset_room()
{
	knocked = 0;
	::reset_room();
}

void create_room()
{
	::create_room();
    add_my_desc("@@my_desc");
    add_exit(FOREST_HP + "forest_o4", "southeast", 0, 1);
    
    add_item(({"boulder", "stone", "rock"}), "The huge boulder, standing high in the middle of the forest. "+
                          "You have no idea how it got here - it looks like it "+
                          "must have dropped from the sky.\n");
    
}

string my_desc()
{
 if(opened)
 {
  return "A huge rock is lying between the trees. You notice a small door "+
         "leading south on the boulder's surface.\n";
 }
 return "A huge rock is lying between the trees.\n";
}



void close_gate()
{
 remove_exit("south");
 tell_room(TO, "The door shuts. If you haven't seen it, you wouldn't believe they "+
               "ever was here.\n");
 opened = 0;
}


void open_gate()
{
 tell_room(TO, "Suddenly a door opens in the lit wall.\n");
 add_exit(FOREST_HP + "inside", "south", 0, 0);
 set_alarm(5.0, 0.0, &close_gate());
 opened = 1;
 knocked = 0;
}

public void init()
{
 ::init();
 add_action("knock_on_boulder", "knock");
 add_action("say_password", "utter");
}

int knock_on_boulder(string a)
{
 if(!strlen(a))
 {
  notify_fail("Knock on what?\n");
  return 0;
 }
 a = lower_case(a);
 if(!parse_command(a, ({}), "knock [on] [the] 'boulder' / 'stone' / 'rock'"))
 {
  notify_fail("Knock on what?\n");
  return 0;
 }
 write("You knock on the boulder, nothing happened, but you feel you attracted "+
       "someone's attention \n");
 knocked = 1;
 return 1;
}

int say_password(string a)
{
 if(!knocked)
 {
  return 0;
 }
 if(tried)
 {
  notify_fail("You feel you need to wait a bit before another attempt.\n");
  return 0;
 }
 if(!decrypt(TP, a))
 {
  tried = 1;
  set_alarm(20.0, 0.0, &remove_flag());
  notify_fail("You must have said something wrong, nothing happens.\n");
  return 0;
 }
 open_gate();
 write("You've said the correct password!\n");
 if(!TP->test_bit("Terel", QUEST_CRYPT_GROUP, QUEST_CRYPT_BIT))
 {
	 TP->catch_msg("You feel more experienced!\n");
	 TP->set_bit(QUEST_CRYPT_GROUP, QUEST_CRYPT_BIT);
	 write_file(QUEST_LOG, capitalize(TP->query_real_name()) +
	   " solved the decryption quest (" + ctime(time()) + ")\n");
	 if(TP->query_exp() < QUEST_CRYPT_REWARD)
		TP->add_exp_quest(TP->query_exp());
	 else
		TP->add_exp_quest(QUEST_CRYPT_REWARD);
	TP->add_prop(PLAYER_I_SOLVED_DEC_Q, 1);	 
 }
 return 1;
}

void remove_flag()
{
 tried = 0;
}

/* The key player read is stored in PLAYER_M_T_KEY prop line after line.
   The first number in that string is length of the key.
   PLAYER_M_T_PASSWORD is a prop containing password vector.
   The decrypted passoword is a resoult of cesar method decryption.

*/
int decrypt(object sender, string said)
{
  string decrypted = "";
  int size, line;
  int *key, *password;
  string s_password, s_key;
  /*He haven't read either of needed parts - cheater or random person.*/
  if(!sender->query_prop(PLAYER_M_T_KEY) || !sender->query_prop(PLAYER_M_T_PASSWORD))
            return 0;
            
  /* 48 is a difference between integer and it's char representation */
  size = sender->query_prop(PLAYER_M_T_KEY)[0] - 48;
  /* Those allocations are needed to use combined indexes in loops below */
  key = allocate(size);
  password = allocate(PASSWORD_SIZE);
  s_key = sender->query_prop(PLAYER_M_T_KEY);
  s_password  = sender->query_prop(PLAYER_M_T_PASSWORD);
  /* 97 is a integer cast of 'a'. I use 0 for 'a' index in LETTERS array */
  for(int i = 0; i < size; ++i)
          /*Additional +1 in s_key index is for first number that is keeping 'size' */
          key[i]  = s_key[i + 1] - 97;
  for(int j = 0; j < PASSWORD_SIZE; ++j)
          password[j] = s_password[j] - 97;
          
  
  for(int j = 0; j < PASSWORD_SIZE; ++j)
  {
          decrypted += LETTERS[(key[j%size] + password[j])%sizeof(LETTERS)];
  }                       
  if(said == decrypted)
          return 1;
  return 0;
}
 
