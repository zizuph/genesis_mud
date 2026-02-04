/*Password to bandit treasure room,
Udana 03/2006*/


#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "../include/defs.h"
#include "/d/Terel/include/Terel.h"


inherit "/std/object";


int *password = allocate(PASSWORD_SIZE);

/* creates a password with new random numbers */
void create_password();

void
create_object()
{
    set_name("parchment");
    add_name("scroll");
    
    set_short("scroll of parchment");
    set_long("A small piece of parchment with a series of letters on it.\n");
    add_prop(CONT_I_WEIGHT, 10);
    add_prop(CONT_I_VOLUME, 10);
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_M_NO_SELL, "You can't sell that!\n");
    create_password();
}

public void init()
{
 ::init();
 add_action("display_password", "read");
}

void create_password()
{
 
 for(int j = 0; j < PASSWORD_SIZE; ++j)
   password[j] = random(sizeof(LETTERS) - 1);
 
}

public int *query_password()
{
 return password;
}

int display_password(string a)
{
 string player_password = "";
 if(a == "parchment" || a == "scroll" )
 {
  write("  ");
  for(int j = 0; j < PASSWORD_SIZE; ++j)
          write("/\\");
  write("_\n");
  write(" |"); 
  for(int j = 0; j < PASSWORD_SIZE; ++j)
  {
          write(LETTERS[password[j]] + " ");
          player_password += LETTERS[password[j]];       
  }
  write("|\n");
  write("  ");
  for(int j = 0; j < PASSWORD_SIZE; ++j)
          write("\\/");
  write("~\n");
  TP->add_prop(PLAYER_M_T_PASSWORD, player_password);
  return 1;
 }
 return 0;
}

