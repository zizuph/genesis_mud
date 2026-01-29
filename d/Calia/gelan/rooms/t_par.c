/*  Tattoo Parlour for new tattoos

coder(s):   Digit & Stexx

history:    11 June 95:
              System reworked replacing old macro arrays with a more
              memory efficient global variable.
              Changed the signs around entirely, so 'more' can be
              used. The textfiles are a combination handwritten, like
              the use sign, or generated from the current arrays of
              variables with the update_signs function, like 
              tattoo_design & tattoo_adj.
                                             - Stexx
            29/4/96    clear customer in leave_inv added  Maniac
            19/5/95    west exit added         Maniac
            26 Mar 95 - created                Digit

purpose:    to give a tattoo or four to a person
exits:      none yet

objects:    tattoo object for person (tob.c)
npcs:       budda (tattoo artist)

quests:     none
special:    tattoo shadow (ta2.c)

to do:      none
bug:        none known
*/

/*
An example shop coded by Nick, some Ideas and part of code taken from
Tricky's shop in hobbitown, and Glykron's hairdresser in Gelan.
*/

#pragma save_binary

#include "defs.h"

#include "/d/Calia/gelan/tattoos/tattoo_defines.h"
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <cmdparse.h>
#include <composite.h>
#include <filter_funs.h>

inherit GELAN_BASE_ROOM;
inherit "/lib/trade";
inherit "/lib/commands";

#include "/d/Calia/gelan/tattoos/tattoo_data.h"
#include "/d/Calia/domain.h"
#include "room.h"

#define SPOUSE_DESIGN 43
#define NUM 4
#define TATTOO_SUBLOC "_tattoo_shadow_desc_"
#define TATTOO_PRICE 1728      /* 1 Plat */
#define GUILDS_PICTURE BASE+"guilds_picture"
#define LOCATIONS_PICTURE BASE+"locations_picture"
#define ADJECTIVES_PICTURE BASE+"adjectives_picture"
#define TATTOOS_PICTURE BASE+"tattoos_picture"
#define PARLOUR_SIGN BASE+"parlour_sign"

object keeper;

public string
reverse_indent(string str)
{
    int i,
        j;
    string temp;

    while (i < strlen(str))
    {
        if (!i)
        {
            j = 70;
            if (j < strlen(str))
            {
                while (str[j..j] != " ")
                    j--;
            }
            else
                j = strlen(str);
            temp = str[i..j] + "\n";
        }
        else
        {
            j = i + 55;
            if (j < strlen(str))
            {
                while (str[j..j] != " ")
                    j--;
            }
            else
                j = strlen(str);
            temp += "               " + str[i..j] + "\n";
            
        }
        i = (j+1);
    }

    return temp;
}

/*
 * Function name: update_signs
 * Description: Auto-generates adjective, guilds, locations, and
 *              designs pictures into text files so the 'more' command
 *              may be used. This function does not auto-invoke, but
 *              is called manually whenever any of the selections arrays
 *              are modified.
 */
void
update_signs()
{
string temp,
       *temparr,
       adj1,
       adj2,
       temp2,
       design;
int i,
    j;
mixed des_index;  

  /* Generate the 'locations' picture */
    if(file_size(LOCATIONS_PICTURE) > -1)
        rm(LOCATIONS_PICTURE);
    temp = "These are the locations you may select:\n";
    temparr = (({}));
    for (i = 0; i < sizeof(m_values(tattoo_cover)); i++)
    {
        temp2 = m_indexes(tattoo_cover)[i] + " : " +
            m_values(tattoo_cover)[i][1];
        temparr += ({sprintf("%-75=s", temp2)});
    }

    temp += implode(temparr, "\n") + "\n";
    write_file(LOCATIONS_PICTURE, temp);

  /* Generate the 'adjectives' picture */
    if (file_size(ADJECTIVES_PICTURE) > -1)
        rm(ADJECTIVES_PICTURE);

    temp = "These are the adjectives you may select:\n";
    temp += sprintf("%-75#s\n", implode(tattoo_adj, "\n"));
    temp += "\n";
    write_file(ADJECTIVES_PICTURE, temp);

  /* Generate the tattoos picture */
    if (file_size(TATTOOS_PICTURE) > -1)
        rm(TATTOOS_PICTURE);

    temp = "These are the designs which you may select:\n";

    for (i = 0; i < sizeof(tattoo_design); i++)
    {
        if (!MASTER_TATTOO->query_guild_design(i) && i != SPOUSE_DESIGN)
        {
            temp2 = i + ":    " + MASTER_TATTOO->make_design(i,
                "<adjective>", "<adjective>");
            temp += reverse_indent(temp2);
        }
    }
    write_file(TATTOOS_PICTURE, temp);
  
  /* Generate the 'guilds/clubs' picture */
    if (file_size(GUILDS_PICTURE) > -1)
        rm(GUILDS_PICTURE);

    temp = "These are the available guild/club tattoos:\n";

    temparr = sort_array(m_indexes(guild_tattoos));

    for (i = 0; i < sizeof(temparr); i++)
    {
        adj1 = guild_tattoos[temparr[i]][1];
        adj2 = guild_tattoos[temparr[i]][2];
        des_index = guild_tattoos[temparr[i]][3];
        temp2 = temparr[i] + ": ";
        temp2 += MASTER_TATTOO->make_design((int)des_index, adj1, adj2); 
        temp += reverse_indent(temp2);
    }
    write_file(GUILDS_PICTURE, temp);
}

reset_room()
{
   if (!keeper) fix_keeper();
}

fix_keeper()
{
   keeper = clone_object(TATTOO_ARTIST);
   keeper->move(this_object());
   tell_room(this_object(), QCTNAME(keeper) + " arrives from the back room.\n");
}

string
picture_descriptions()
{
   string desc;
   
   desc = "The pictures showcase various tattoos. " +
   "Try examining 'adjectives', 'tattoos', 'guilds' and "+
   "'locations'.\n";
   return desc;
}


string
guilds_desc()
{
   this_player()->more(read_file(GUILDS_PICTURE));
    return "";
}

string
adjs_desc()
{
   this_player()->more(read_file(ADJECTIVES_PICTURE));
  return "";
}


string
tats_desc()
{
   this_player()->more(read_file(TATTOOS_PICTURE));
  return "";
}


string
bodylocs_desc()
{
   this_player()->more(read_file(LOCATIONS_PICTURE));
  return "";
}


/*
* Function name:   create_gelan_room
* Description:     Initialize this room
* Returns:
*/
public void
create_gelan_room()
{
   set_short("Tattoo Parlour");
   set_long(
      "You have entered a smoke filled room. There is a large counter "+
      "in front of a door that leads to a back room. The only other exit "+
      "is back the way you came. "+
      "There are pictures on the wall showing you various tattoos. " +
      "You also notice a box in the corner and a sign for you to read." +
      "\n");
   
   add_prop(ROOM_I_INSIDE, 1);     /* this room is inside */
   
   
   add_item("sign", "A rather lengthy sign with some information you "+
      "should probably read.\n");
   add_item("pictures", "@@picture_descriptions");
   add_item("adjectives", "@@adjs_desc");
   add_item("tattoos", "@@tats_desc");
   add_item("locations", "@@bodylocs_desc");
   add_item("guilds","@@guilds_desc");
    add_item("box","This box has a slit in the top and the words "+
        "\"idea <tattoo idea>\" written on it.\n");
   
   config_default_trade();
   
   add_exit(GELAN_ROOMS+"hairdresser", "west");

    setuid();   
    seteuid(getuid());

    set_alarm(1.0, 0.0, reset_room);
}


/*
* Function name:   do_read
* Description:     If a player wants to know what instuctions can be
*                  used
* Arguments:       str - string, hopefully "sign"
* Returns:         1/0
*/
int
do_read(string str)
{
   NF("Read what?\n");
   if (str != "sign")
      return 0;
   
   this_player()->more(read_file(PARLOUR_SIGN));

   return 1;
}

int
check_keeper()
{
   if (keeper && present(keeper,this_object()))
      return 1;
   else
      return 0;
}


/*
* Function name:   do_idea
* Description:     let the player put an idea in the idea box
* Returns:         1 on sucess
* Arguments:       str - the idea
*/
int
do_idea(string str)
{
  notify_fail("What was your idea again?\n");
  
  if(!str || !strlen(str))
    return 0;

   log_file("tattoo_ideas", ctime(time()) + " (" + TP->query_name() +
      ")\n" + str + "\n\n");
   write("Ok, you placed an idea in the box.\n");
   return 1;
}

/*
* Function name:   init
* Description:     Is called for each living that enters this room
* Returns:
*/
void
init()
{
    object old_obj;
   ::init();   /* You MUST do this in a room-init */
   add_action("do_read", "read");
   add_action("do_idea", "idea");

    if (present("_stexxs_tattoo_object", this_player()))
    {
        old_obj = present("_stexxs_tattoo_object", this_player());
        if (domain(old_obj) == "Immortal")
        {
            old_obj->remove_object();
            clone_object("/d/Calia/gelan/tattoos/tattoo")->move(this_player(),1);
        }
    }
}

/* Check to make sure it registers if a customer leaves */ 
void
leave_inv(object ob, object to) 
{
    ::leave_inv(ob, to);

    if (living(ob) && objectp(keeper))
        keeper->clear_customer(ob); 
}
