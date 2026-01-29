/* This object records the history of sponsoring among
 * the knights. It'll be automatically updated.
 * The tapestry in the knights spur will call on this
 * data to display the current version.
 *
 * Aridor, 09/95
 */

#include <std.h>
#define ADMIN      "/d/Krynn/solamn/vin/knight/admin/admin"
#define SAVE_ME    "/d/Krynn/solamn/vin/knight/admin/sponsor_tree"
#define FILE       "/d/Krynn/solamn/hctower/spur/tree/"

mapping squires = ([]);
/* the format of each element in the mapping is:
 *       "squire":({"sponsor",id})
 * where id is a binary encoded number with this meaning:
 * 1: layman
 * 2: left the guild
 * 4: removed from game
 * 8: wizzed
 */

void
create()
{
    seteuid(getuid(this_object()));
    restore_object(SAVE_ME);
    set_alarm(2.0,0.0,"check_all");
}

void
make_tree(string file, string who, int offset, mapping knight, int first)
{
    string extras = "";
    string *next = knight[who];
    int i,extra=0,id;

    id = squires[who][1];
    //set_this_player(find_living("aridor"));
    //dump_array(who);
    //dump_array(knight);
    //dump_array(next);
    extras += sprintf("%" + (first?0:offset) + "s->%s","",capitalize(who));
    if (id & 1)
      {
	  extra++;
	  extras += ""; /*"!" not necessary anymore, removed to avoid problems :) */
      }
    if (id & 2)
      {
	  extra++;
	  extras += "*";
      }
    if (id & 4)
      {
	  extra++;
	  extras += "#";
      }
    if (id & 8)
      {
	  extra++;
	  extras += "@";
      }
    write_file(FILE + file,  extras);
    write_file(FILE + "tree",extras);

    if (next && sizeof(next))
      for(i=0;i<sizeof(next);i++)
	make_tree(file,next[i],offset+2+strlen(who)+extra,knight,(i==0));
    else
      {
	  write_file(FILE + file,  "\n");
	  write_file(FILE + "tree","\n");
      }
}

void
start_make_tree(string file, string who, int offset, mapping knight, int first)
{
    rm(FILE + file);
    make_tree(file,who,offset,knight,first);
    write_file(FILE + "tree","\n");
}

void
end_make_tree()
{
    write_file(FILE + "tree","\n\n\n!=layman  @=wizzed  *=left guild  " +
	       "#=player no longer exists\n\n" +
	       "Tree is current as of: " + ctime(time()) + "\n\n");
}

void
update_trees2(mapping knight)
{
    seteuid(getuid(this_object()));
    rm(FILE + "tree");
    write_file(FILE + "tree","\n\nKnights of Solamnia Sponsorship Tree\n\n");

    set_alarm(1.0,0.0,&start_make_tree("kayen","kayen",0,knight,1));
    set_alarm(2.0,0.0,&start_make_tree("bayerd","bayerd",0,knight,1));
    set_alarm(3.0,0.0,&start_make_tree("ashlar","ashlar",0,knight,1));
    set_alarm(4.0,0.0,&start_make_tree("elgarhad","elgarhad",0,knight,1));
    set_alarm(5.0,0.0,&start_make_tree("katanga","katanga",0,knight,1));
    set_alarm(6.0,0.0,&start_make_tree("korlis","korlis",0,knight,1));
    set_alarm(7.0,0.0,&start_make_tree("danov","danov",0,knight,1));
    set_alarm(8.0,0.0,&start_make_tree("carridin","carridin",0,knight,1));
    set_alarm(9.0,0.0,&start_make_tree("finglas","finglas",0,knight,1));
    set_alarm(10.0,0.0,&start_make_tree("croft","croft",0,knight,1));
    set_alarm(11.0,0.0,&start_make_tree("mathrim","mathrim",0,knight,1));
    set_alarm(12.0,0.0,&start_make_tree("ruskin","ruskin",0,knight,1));
    set_alarm(15.0,0.0,"end_make_tree");

    seteuid(getuid(this_object()));
    save_object(SAVE_ME);
}
/* This function takes the mapping of squires and
 * builds files from it. I hope this works out...
 */
void
update_trees()
{
    mapping knight = ([]);
    int i;
    string *squire_names = m_indexes(squires);
    int size = sizeof(squire_names);
    
    for(i=0;i<size;i++)
      if (knight[squires[squire_names[i]][0]])
	knight[squires[squire_names[i]][0]] += ({squire_names[i]});
      else
	knight += ([ squires[squire_names[i]][0]:({squire_names[i]}) ]);
    
    set_alarm(1.0,0.0,"update_trees2",knight);
}

/* Check everyone in the list to see if they are
 * still a player, or maybe have wizzed.
 */
void
check_all()
{
    string *knight = m_indexes(squires);
    int i,tmp,size = sizeof(knight);
    
    for(i=0;i<size;i++)
      {
	  tmp = (ADMIN)->query_knight_status(knight[i]);
	  if (tmp > 10)
	    squires[knight[i]][1] |= 1;
	  else 
	    squires[knight[i]][1] &= 0;
	  if (!tmp)
	    if (!(SECURITY)->exist_player(knight[i]))
	      squires[knight[i]][1] |= 4;
	    else
	      squires[knight[i]][1] |= 2;
	  if ((SECURITY)->query_wiz_level(knight[i]))
	    squires[knight[i]][1] |= 8;
      }

    update_trees();
}

/* Add a new sponsor-squire relationship.
 */
void
add_new_relation(string knight, string squire, int lay)
{
    squires += ([squire:({knight,lay})]);
    update_trees();
}

void
left_guild(string who)
{
    if (!squires[who])
      return;

    squires[who] = ({squires[who][0],squires[who][1] | 2});
    update_trees();
}

void
remove_item(string who)
{
    squires = m_delete(squires, who);
    update_trees();
}

void
query_info(string who)
{
    dump_array(squires[who]);
}
