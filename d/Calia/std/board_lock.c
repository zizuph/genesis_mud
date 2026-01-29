/* A standard bulletin board with a few extras.
 * created by Shiva@Genesis
 */

#pragma save_binary

inherit "/std/board";

#include <stdproperties.h>
#include <std.h>
#include <macros.h>

#define DEBUG_ON
#undef DEBUG_ON

#define EDIT_OBJECT   "/std/edit"
#define NF(x)         notify_fail(x)
#define LOCKED(x)     (extract(x, -1) == "~")

#ifdef DEBUG_ON
#define DEBUG(x) this_interactive()->catch_msg(x + "\n")
#else
#define DEBUG
#endif

static int lock_lvl = (WIZLEV_LORD + 1);
static int lock_access = 0;
static int unlock_access = 0;
static string extra_short = " is posting a note";

void init()
{
  ::init();

  add_action("start_writing", "note");
  add_action("lock", "lock");
  add_action("unlock", "unlock");
}

void set_lock_lvl(int lvl)
{
  if (!fuse)
  {
    lock_lvl = lvl;
  }
}

void set_lock_access(mixed l)
{
  if (!fuse)
  {
    lock_access = l;
  }
}

int check_lock()
{
  return (stringp(lock_access) ? check_call(lock_access) :
      lock_access);
}

void set_unlock_access(mixed l)
{
  if (!fuse)
  {
    unlock_access = l;
  }
}

int check_unlock()
{
  return  (stringp(unlock_access) ? check_call(unlock_access) : 
      unlock_access);
}

/* Keeps a note from scrolling off a board.  Locked notes
 * do not count towards the max number of notes allowed on
 * a board.
 */
int lock(string str)
{
  int note;

  NF("Lock what?\n");
  if (!strlen(str))
    return 0;

  NF("You are not allowed to do that.\n");
  if (this_object()->check_lock() ||
      (no_special_fellow() &&
      this_player()->query_wiz_level() < lock_lvl))
    return 0;

  NF("Lock which note?\n");
  if (!sscanf(str, "%d", note) && !sscanf(str, "note %d", note))
    return 0;

  NF("Not that many notes.\n");
  if (note < 1 || note > msg_num)
    return 0;

  note--;
  notes++;

  NF("That note has been locked already.\n");
  if (LOCKED(headers[note][1]))
    return 0;

  DEBUG("Old path: " + board_name + "/" + headers[note][1]);

  rename(board_name + "/" + headers[note][1],
         board_name + "/" + (headers[note][1] += "~"));

  DEBUG("New path: " + board_name + "/" + headers[note][1]);

  write("Note " + (note + 1) + " is locked on the board.\n");

  return 1;
}

int unlock(string str)
{
  int note;
  string new_name;

  NF("Unlock what?\n");
  if (!strlen(str))
    return 0;

  NF("You are not allowed to do that.\n");
  if (this_object()->check_unlock() ||
      (no_special_fellow() &&
      this_player()->query_wiz_level() < lock_lvl))
    return 0;

  NF("Unlock which note?\n");
  if (!sscanf(str, "%d", note) && !sscanf(str, "note %d", note))
    return 0;

  NF("Not that many notes.\n");
  if (note < 1 || note > msg_num)
    return 0;

  note--;

  NF("That note is not locked.\n");
  if (!sscanf(headers[note][1], "%s~", new_name))
    return 0;

  notes--;

  DEBUG("Old path: " + board_name + "/" + headers[note][1]);

  rename(board_name + "/" + headers[note][1],
         board_name + "/" + (headers[note][1] = new_name));

  DEBUG("New path: " + board_name + "/" + headers[note][1]);

  write("Note " + (note + 1) + " is no longer locked on the board.\n");

  return 1;
}

int start_writing(string str)
{
  int ret = new_msg(str);

// Add my LIVE_S_EXTRA_SHORT when someone starts posting a note
  if (ret && sizeof(filter(all_inventory(this_player()),
      "find_editor", this_object())))
  {
    this_player()->add_prop(LIVE_S_EXTRA_SHORT, extra_short);
    DEBUG("LIVE_S_EXTRA_SHORT = \"" +
        this_player()->query_prop(LIVE_S_EXTRA_SHORT) + "\"");
  }

  return ret;
}

// Looks for an editor object in an array of objects
int find_editor(object ob)
{
  return (ob && MASTER_OB(ob) == EDIT_OBJECT);
}

/* Make sure locked notes aren't removed when the board
 * scrolls.  Removes LIVE_S_EXTRA_SHORT when finished
 * posting, if appropriate.
 */
int done_editing(string str)
{
  int i = 0;

  while(msg_num >= notes)
  {
    if (LOCKED(headers[i][1]))
    {
      i++;
      DEBUG("Note " + i + " skipped for deletion");
      continue;
    }

    discard_message(headers[i][1]);
    headers = exclude_array(headers, i, i);
    msg_num--;
  }

  if (this_player()->query_prop(LIVE_S_EXTRA_SHORT) == extra_short)
    this_player()->remove_prop(LIVE_S_EXTRA_SHORT);

  return ::done_editing(str);
}

void load_headers()
{
  int i;

  ::load_headers();

  for (i = 0; i < msg_num; i++)
  {
    if (LOCKED(headers[i][1]))
      notes++;
  }
}

void set_extra_short(string short)
{
  if (!short)
    extra_short = "";
  else
    extra_short = short;
}