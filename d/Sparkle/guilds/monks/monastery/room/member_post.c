/*******************************************************************\
| MEMBER_POST.C                                                     |
\*******************************************************************/

/*
 * 08/02/01 Arandir     Fixed aliases
 * 03/09/09 Arandir     Added the elders alias
 * 03/09/09 Arandir     Added the elders alias
 * 03/09/07 Arandir     Fixed missing mail notification
 * 03/08/04 Arandir     Fixed sunlight reference
 * 03/05/17 Arandir	Ported to new area
 * 02/06/13 Manat       Added the council and guildmaster aliases
 * 00/12/26 Manat       Fixed typos
 * 98/06/14 Cirion	Created
 *
 */

#include <stdproperties.h>

#include "../defs.h"

inherit M_ROOM_BASE;

inherit "/d/Genesis/lib/post";

inherit DG_TEXT_LIBS;

//-------------------------------------------------------------------

void create_room ()
{
  set_short ("quiet room");
  set_long ("Standing in the center of this circular room is " +
            "a small desk of pine. Inscribed on the smooth stone " +
            "floor is a circle painted gold, within which are " +
            "written letters. A square window in the north wall " +
            "provides light for the room, along with a small " +
            "iron lamp that rests on the desk.\n");

  add_prop (ROOM_I_INSIDE, TRUE);

  add_exit ("hall_upper_north", "east");

  dg_add_entrance ("east", "You enter a small, silent chamber.");

  add_item (({ "desk", "pine desk", "pine", "table" }),
            "The small desk is simply build from pine. The " +
            "front of the desk contains many small cubbyholes, " +
            "within which correspondences can be placed. " +
            "Sitting on the desk is a small bottle of ink and " +
            "a glass cube, serving as a rest for a feather " +
            "quill.\n");
  add_item (({ "stand", "glass stand" }),
             "The small cubic stand is made from thick, opaque " +
             "glass.\n");
  add_item (({ "quill", "pen", "feather" }),
            "The feather is used for composing letters.\n");
  add_item (({ "glass", "window" }),
            "The leaded glass of the window is designed to let in " +
            "a plenty of sunlight. Its frame is made from thin slats " +
            "of wood, and it is criss-crossed by shafts of iron " +
            "to hold the glass in place.\n");
  add_item (({ "lamp", "lantern" }),
            "The small iron lamp is intricate. Its light shines " +
            "from small, clover shaped holes of its tapered " +
            "hood, and shines down in the desk in dappled " +
            "patterns.\n");
  add_item (({ "hole", "holes", "cubby", "cubbyhole", "cubbyholes" }),
            "Inset into the front of the desk are numerous " +
            "cubbyholes, within which correspondences are " +
            "placed, and into which outgoing mail is put when " +
            "it is sent.\n");
  add_item (({ "letters", "letter" }),
            "They appear to form words that should be read.\n");
  add_item (({ "circle", "gold circle", "gold leaf" }),
            "A modest display of wealth, a circle of gold leaf " +
            "has been painted upon the floor, and within it, " +
            "words are written.\n");

  add_cmd_item (
    ({ "letter", "letters", "floor", "ground", "words" }),
    ({"read"}),
    "In silence shall we be cradled.\n" +
    dg_embed_action ("looks down at the floor and reads the words written there."));
  add_cmd_item (
    ({ "sun", "stars", "light", "sunlight", "starlight" }),
    ({ "feel", "enjoy" }),
    dg_embed_when_night ("The starlight feels sharp and cold where it falls on your face.") +
    dg_embed_when_not_night ("The sunlight feels warm on your face.") +
    "\n" +
    dg_embed_action ("basks in the light coming in through the window."));
  add_cmd_item (
    ({ "lamp", "lantern" }),
    ({ "get", "take" }),
    "It seems to be firmly bolted to the table.\n" +
    dg_embed_action ("tried to take the lantern from the table, but finds that it is bolted down."));
}

//-------------------------------------------------------------------

void init ()
{
  ::init ();
  post_init ();
}

void leave_inv (object oWhat, object oWhere)
{
  ::leave_inv (oWhat, oWhere);
  post_leave_inv (oWhat, oWhere);
}

void add_aliases (object oReader)
{
  // The post documentation says add_alias should be
  // used, but there is no such function in the
  // reader, set_alias is present instead.
  oReader->set_alias ("guildmaster", M_MASTERS_ACTIVE);
  oReader->set_alias ("council", m_get_council_members ());
  oReader->set_alias ("elders", m_get_elder_members ());
}

//-------------------------------------------------------------------

/*
 * Function name : query_mail
 * Description   : This function is called when a player logs in to
 *                 inquire about the state of his mailbox.
 *   iSilent       : True to not tell about the mail
 * Returns       : Mail status
 *
 */

int query_mail (int iSilent)
{
  int iMail = MAILCHECKER->query_mail ();

  if (!iSilent)
  {
    switch (iMail)
    {
      case MAIL_SOME_NEW:
        write (dg_framed_text ("New mail awaits you in the monastery post office."));
        break;
      case MAIL_SOME_UNREAD:
        write (dg_framed_text ("Unread mail awaits you in the monastery post office."));
        break;
    }
  }

  return (iMail);
}

//-------------------------------------------------------------------

