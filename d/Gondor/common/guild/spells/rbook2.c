#pragma save_binary

inherit "/std/spells";

#include "/secure/std.h"
#include "/sys/tasks.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include "/sys/stdproperties.h"
#include "/sys/formulas.h"
#include "/d/Gondor/elessar/lib/binbit.h"
#include <spell_funs.h>
#define SP_HEAL_MANA 60
#define SP_HEAL_INGR ({ "_heal_spell_herb_" })
#define SP_REST_MANA 30
#define SP_REST_INGR ({ "_rest_spell_herb_" })
#define SP_SUMM_MANA 10
#define STAND_DIR "/d/Gondor/common/guild/spells/"
#define SPELLTXT STAND_DIR+"text/"
#include "ranger_spell_defs.h"
#include "nightvision.c"
#include "heal.c"
#include "rest.c"
#include "cleanse.c"
#include "pigeon.c"
#include "elbereth.c"
/*
#include "herblore.c"
*/
#include "speedgrowth.c"

string spells_known;

void
create_spells()
{
    set_name("book");
    add_name("ranger_spell_book");
    add_name("spellbook");
    set_adj("brown");
    set_adj("little");
    set_short("little brown book");
    set_long(
	  "The brown leatherbound book still smells of animal hides, \n"+
          "fresh as if it has just been made. You can sense a strange \n"+
          "feeling of magic about it, confirmed by a few words in \n"+
	  "swirling black letters written on the front: \n"+
	  "          Magic of the Rangers.\n "+
    "There is an index to read in the first pages.\n");

    add_item(({"letters","black letters","words"}), "The elaborate black letters "
	+ "are not easy to read, but you find\n"+
	  "that they read: Magic of the Rangers.\n");
    add_prop(OBJ_I_WEIGHT, 250);
    add_prop(OBJ_I_VOLUME, 503);
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_GIVE, "@@env_check");
    add_prop(OBJ_S_WIZINFO, "@@wizinfo");
}

void
init()
{
    add_action("do_read","read");
    add_action("do_tear","tear");
}

string
query_auto_load()
{
  if (strlen(spells_known) > 1)
    return MASTER_OB(this_object()) + ":" + spells_known;
  return MASTER_OB(this_object()) + ":";
}

void
init_arg(string str)
{
  if (str && str != "0") spells_known = str;
  set_alarm(2.5,0.0,"setup_ranger_spells");
  return;
}


/* Function: query_spell_known
 * Description: Checks if the player knows a specific spell.
 * Arguments: The code-letters for the spell.
 * Returns: 1 if player has learned the spell.
 *          0 if not.
 */

int
query_spell_known(string str)
{
  int i;
  string *sp_arr;
  if (!str) return 0;
  if (!spells_known) return 0;
  sp_arr = explode(spells_known,"#");
  while (i<sizeof(sp_arr))
    {
      if (str == sp_arr[i]) return 1; /* Player knows this spell. */
      i++;
    }
  return 0;  /* Player didn't know the spell */
}

int
scribe_spell(string str)
{
  string *sp_arr;
  sp_arr = ({ });
  if (member_array(str,RSPELL_CODENAME)==-1) return 0;
  if (query_spell_known(str)) return 0;
  if (query_rspell_total_levels() + query_rspell_level(str) >
    MAX_LEVELS[query_bin_bits(1,16,2,TP)]) {
      write("There are not enough pages left in your spellbook!\n");
    return 1;
    }
  if (spells_known) {
  sp_arr = explode(spells_known,"#");
  sp_arr += ({ str });
  }
  else sp_arr = ({ str });
  spells_known = implode(sp_arr,"#");
  write_file("/d/Gondor/log/spellbook",ENV(TO)->query_name()+" added "+capitalize(RSPELL_NAME[query_rspell_no(str)])+". "+ctime(time())+".\n");
  return 1;
}

int
erase_spell(string str)
{
  string *sp_arr;
  string sp_name, sp_code;
  int i;
  sp_arr = ({ });
  sp_code = query_rspell_codename(lower_case(str));
  NF("That spell is not in the book.\n");
  if (sp_code == "No code") return 0;
  if (!query_spell_known(sp_code)) return 0;
  if (!spells_known) return 0;
  sp_arr = explode(spells_known,"#");
  i = member_array(sp_code,sp_arr);
  sp_arr = exclude_array(sp_arr,i,i);
  if (sizeof(sp_arr)>0)
    spells_known = implode(sp_arr,"#");
  else spells_known = "";
  write("The "+str+"-spell is erased from the spellbook.\n");
  return 1;
}

string
wizinfo() {
   return "More info? Simply read the book, and you'll know all about it.\n";
}

string
add_index()
{
  string txt, *sp_arr;
  int sn, i;
  if (!spells_known) return "The rest of the book contains only blank pages.\n";
  sp_arr = ({ });
  sp_arr = explode(spells_known,"#");
  if (!sizeof(sp_arr)) 
    return "The rest of the book contains only blank pages.\n";
  txt = "";
  while (i < sizeof(sp_arr)) {
    txt = txt + "Chapter "+(i+1)+" ................. " 
      + capitalize(RSPELL_NAME[query_rspell_no(sp_arr[i])])+".\n";
    i++;
    }
  return txt+"\n";
}

int
do_read(string str)
{
  object tp;
  string *sp_arr;
  int page;
  
  notify_fail("Read what?\n");
  if (!str)
    return 0;
  
  tp = this_player();
  str = lower_case(str);
  
  if (str == "book" || str == "brown book" || str == "little brown book")
    {
      notify_fail("The little brown book has several chapters.\n"
		  + "Read the index to make a selection.\n");
      return 0;
    }
  if (str == "index")
    {
      say(QCTNAME(tp) + " opens " + tp->query_possessive() +
	  " little brown book and starts reading it.\n");
      write("You open the little brown book on the index. You read:\n"+
	    "    Magic in the Nature as used by Rangers and Clerics.\n"
	    + add_index() +"\n");
      return 1;
    }
  if (sscanf(str,"chapter %d", page) != 1) {
    NF("Read what?\n"); return 0; }
  if (page <=0) { write("There is no such chapter; maybe you should read the index?\n");
		  return 1; }
  sp_arr = explode(spells_known,"#");
  if (sizeof(sp_arr) < page) {
    write("There aren't that many chapters.\n"); return 1; }
  write("You open to where chapter "+page+" begins, and start to read.\n\n");
  seteuid(getuid(TO));
  cat(SPELLTXT+RSPELL_NAME[query_rspell_no(sp_arr[page-1])]+".txt");
  return 1;
}

do_tear(string str)
{
  notify_fail("If you want to get rid of the little brown book forever,\n"+
	      "do 'tear the brown book apart'.\n");
  str = lower_case(str);
  if (str != "brown book apart" && str != "the brown book apart")
    return 0;
  
  write("You tear the little brown book apart.\n");
  say(QCTNAME(TP) + " tears " + TP->query_possessive() + 
      " brown book apart.\n");
  remove_object();
  return 1;
}

/* Wizards may give the book to someone else */
int
wiz_check()
{
  if (!this_player()) return 1;
  if (this_player()->query_wiz_level())
    {
      call_out("check_carry",1);
      return 0;
    }
  else
    if (this_player()->query_npc())
      {
        call_out("check_carry",1);
        return 0;
      }
    else
      return 1;
}

string
query_spells_in_book()
{
  return add_index();
}

int
query_spell_time(string str)
{
    switch(str)
    {
      case "elbereth":
        return 0;
      case "heal":
        return 3;
      case "cleanse":
        return 7;
      case "rest":
        return 4;
      case "nightvision":
        return 4;
      case "whistle":
        return 0;
      case "speedgrow":
        return 8;
    }
    return ::query_spell_time(str);
}
