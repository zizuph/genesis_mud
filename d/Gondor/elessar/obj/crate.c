inherit "/std/receptacle";

#include <macros.h>
#include "/sys/stdproperties.h";
#include "/d/Gondor/defs.h"

#define NOTE_TEXT "/d/Gondor/minas/harlond/texts/"

int note_no;

create_container() {
   set_name("crate");
  set_pname("crates");
    set_adj("large");
  set_cf(TO);
  add_adj("wooden");
    set_long(BSN("This is a large wooden crate, with a note stuck " +
      "to one side. The crate looks sturdily built, and can probably "+
      "hold quite a bit."));
   add_prop(CONT_I_WEIGHT,     6000);   /* It weighs 4 Kg            */
   add_prop(CONT_I_MAX_WEIGHT, 26000);   /* It can contain up to 20 Kg  */
   add_prop(CONT_I_VOLUME,     8000);   /* It measures 8 Ltr         */
   add_prop(CONT_I_MAX_VOLUME, 100000);   /* It can contain 100 Ltr       */
   add_prop(CONT_I_RIGID, 1);            /* It is a rigid object   */
   add_prop(CONT_I_REDUCE_VOLUME,150);
   add_prop(CONT_I_REDUCE_WEIGHT,150);
   add_prop(OBJ_I_VALUE,90);    /* Value ?? cc*/
   add_prop(OBJ_M_NO_SELL,"@@no_sell");
  add_prop(CONT_I_CLOSED,1);
}

query_recover() { return MASTER + ":"; }

mixed
no_sell()
{
  if(sizeof(all_inventory(TO)))
    return BSN("Luckily you notice that the chest is not empty just " +
      "before you sell it. Perhaps you should remove everything from " +
      "the chest before you sell it? ");
  return 0;
}

init()
{
  ::init();
  add_action("read_note","read");
}

read_note(string str)
{
  if (!str) { notify_fail("Read what? The note?\n"); return 0; }
  if (str != "note" && str != "note on crate") return 0;
  write("You read the note that is stuck on the crate.\n");
  cat(NOTE_TEXT+note_no+".txt");
  return 1;
}

int
open(object ob)
{
  write("The top of the crate is nailed shut. You can't open it.\n");
  return 3;
}

