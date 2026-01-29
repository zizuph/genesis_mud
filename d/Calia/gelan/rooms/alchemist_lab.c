
/*  
    Alchemist's laboratory in Gelan.

    coder(s):   Maniac

    history:
        5/4/98       further search options added  Maniac
       24/1/97       further search options added  Maniac 
       15/6/95       typo corrected                Maniac
       25/9/95       bug corrected                 Maniac
        1/5/95       Easier to take flask          Maniac
        28.2.95      Created                       Maniac   

    Comments: Bulk of the Gelan alchemist quest is carried out here.
*/


#pragma save_binary

inherit "/std/room";
#include "room.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include GUARD_INCLUDE
#include ALCHEMIST_QUEST

int book = 1;
int flask = 1;

void
reset_room()
{
}

void
reset_notebook()
{
    book = 1;
}

void
reset_flask()
{
    flask = 1;
}


string
flask_item()
{
     if (!flask)
         return "";
     else
         return "There is a glass flask sitting loose among the " +
                "equipment.\n";

}


void
create_room() 
{
   set_short("Alchemist's laboratory");

   set_long("This is more like it, a genuine alchemist's laboratory, " +
          "complete with charred walls caused by the explosions that " +
          "frequent any self respecting alchemist's place of work, " +
          "a wide variety of odd shaped glass equipment containing " +
          "bubbling, steaming liquids, a shelf full of note books " +
          "that probably chronicle several hundred years of ambitious " +
          "and often failed experiments, and a cabinet full of bottles " +
          "containing suspicious looking coloured liquids. Set in the " +
          "ceiling is a glass skylight, doubling as an outlet for " +
          "noxious gases and an observatory of the stars and planets.\n");

  add_item(({"cabinet", "bottles", "liquids"}), 
       "The cabinet contains a number of bottles of liquids that " +
       "Raspatoon " +
       "mixes together during his experiments. Lord knows what " +
       "goes into these liquids, the names on the labels look " +
       "very unfamiliar.. perhaps they're Raspatoon's very own " +
       "concoctions.\nA plaque on the cabinet states: " + 
       "CAUTION! MAY CAUSE EXPLOSIONS!\n");

  add_cmd_item(({"labels", "names", "names on the labels"}),
                "read", "@@names_long");
  add_item(({"labels", "names", "names on the labels"}), 
        "@@names_long");

  add_item("flask", "@@flask_item");

  add_item(({"skylight", "ceiling"}), 
      "A large window is set in the ceiling, and is always left " +
      "slightly ajar to let out any vapours from experiments. At " +
      "night it provides a nice observatory.\n");

  add_item(({"notebooks", "books", "shelf", "old books", "ancient books",
             "note books", "old note books", "ancient note books", "new note books",
             "new books", "old notebooks", "new notebooks", "ancient notebooks", 
             "piles", "old piles", "new piles", "ancient piles" }), 
      "There are several piles of books, ranging from the ancient " +
      "ones that are nearly falling apart, to old ones that look " +
      "pretty tattered, to new ones that seem currently in use.\n");

  add_item(({"wall", "walls"}), 
       "There seem to have been some pretty nasty explosions here " +
       "in the past, because the walls are very charred.\n");

  add_item(({"equipment", "glass equipment"}), "@@equip_long"); 
  add_prop(ROOM_I_INSIDE,1);  /* This is a real room */

  add_prop(OBJ_S_SEARCH_FUN, "do_search");

  add_exit(GELAN_ROOMS + "alchemist","east",0);

  reset_room();
}


string
names_long()
{
    object tp = this_player();

    string str = "Each bottle is labelled, and the names on the " +
        "labels look very unfamiliar. "; 

    if (tp->query_skill(SS_LANGUAGE) < AQ_LANGUAGES_MIN)
        return str + "The names are written in some obscure " +
             "alchemical language that your skill is currently " +
             "insufficient to decipher.\n";
    else return str + "You skilfully decipher the names as " +
        "follows: " + 
        (GELAN_OBJECTS + "glass_flask")->agent_names() +
        ".\n";
}


/* Stop people taking flask or notebook from room */
void
leave_inv(object ob, object dest)
{
    object b, f;

    ::leave_inv(ob, dest);
    if (f = present(AQ_FLASK_NAME, ob)) {
        ob->catch_msg("You notice the " + f->short() + " magically " +
                      "removed from your possessions.\n");
        f->remove_object();  
    }
    if (b = present(AQ_BOOK_NAME, ob)) {
        ob->catch_msg("You notice the " + b->short() + " magically " +
                      "removed from your possessions.\n");
        b->remove_object();
    }
}


string
do_search(object searcher, string str)
{
    object b;
    string s, s1, s2;

    if ((str == "shelf") ||
        (sscanf(str, "shelf %s", s) == 1))
        return "There is nothing interesting about the shelf, " +
               "presumably what you are trying to do is search " +
               "the `books' (aka `notebooks' or `piles').\n";

    if (sscanf(str, "%s for %s", s1, s2) == 2) 
        str = s1; 

    if (str == "books" || str == "notebooks" || str == "piles" || str == "note books") 
        return "But there are so many books on the shelf" +
               ", which type of book do you want to search?\n";

    if (str == "old books" || str == "old notebooks" || 
        str == "old pile" || str == "old piles" || 
        str == "old note books")  
        if (searcher->query_skill(SS_AWARENESS) < 
                      random(AQ_AWARENESS_ROLL_MAX))
            if (!book) 
               return 0;
            else 
               return "Hmm, you couldn't find the right notebook " +
                 "in the pile of old books that time, but you're " +
                 "sure it should be in there somewhere. The " +
                 "old books are all mixed up. Raspatoon " +
                 "isn't terribly well organised.\n";
        else
            if (!book)
                return 0;
            else {
               b = clone_object(GELAN_OBJECTS + "notebook");
               if (b->move(searcher) == 0) {
                   book = 0;
                   tell_room(environment(searcher), QCTNAME(searcher)
                        + " seems to have found a useful book.\n",
                          searcher);
                   return "You find a book that looks relevant " +
                          "and take it from the shelf.\n";
               }
               else {
                   b->remove_object();
                   searcher->command("duh");
                   return "You spot a relevant book but have " +
                          "so much stuff in your inventory that you can't " +
                          "take it. When you look back at the " +
                          "shelf, you forgot where you saw it.\n";
               }
           }
    return 0;
}


string
equip_long()
{
   string str = 
      "There is much glass laboratory equipment here: flasks of all " +
      "kinds, spheres, beakers and tubing. Much of it is connected " +
      "up and being used in long term experiments.";
   if (flask) str += " There is a glass flask sitting loose among " +
                      "the equipment.\n"; 
   else str += "\n";
   return str;
}


int
do_get(string str)
{
    string s1, s2;
    object f;
    object tp = this_player();


    if (!str)
       return 0;

    if ((lower_case(str) == "liquids") || (lower_case(str) == "liquid") || 
        (member_array(lower_case(str), 
          (GELAN_OBJECTS+"glass_flask")->query_agents()) > -1))  {
         tp->catch_msg(capitalize(str) + " can't be taken.. but " +
                       "think about how one transports liquids from one " +
                       "container to another.\n");
         return 1;
    }

    if (str == "flask" || str == "glass flask")
        str += " from equipment";

    if (sscanf(str, "%s from %s", s1, s2) != 2) { 
        notify_fail("Take what from what?\n");
        return 0;
    }

    if ((s1 == "flask" || s1 == "glass flask") &&
        (s2 == "equipment" || s2 == "glass equipment")) {
        if (!flask) {
            tp->catch_msg("You find no glass flask in the equipment.\n");
            return 1;
        }
        else {
            f = clone_object(GELAN_OBJECTS + "glass_flask");
            if (f->move(tp) != 0) {
                tp->catch_msg("You are too heavily loaded to " +
                              "get the flask.\n"); 
                f->remove_object();
                return 1;
            }
            else {
                tp->catch_msg("You take the glass flask from the " +
                              "equipment.\n");
                tell_room(environment(tp), QCTNAME(tp) + " takes " +
                    "a glass flask from the equipment.\n", tp); 
                flask = 0;
                return 1;
            }
        }
    }
    notify_fail("Take what from what?\n");
    return 0;
}


void
init() 
{
    ::init();
    add_action(do_get, "take");
    add_action(do_get, "get");
}
