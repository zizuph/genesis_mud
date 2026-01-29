inherit "/std/object";
#include <macros.h>
#include <stdproperties.h>

void
create_object()
{
  set_name("book");
  set_short("blackened stained book");
  set_long("On the verge of falling apart, this tattered book "+
     "is stained and coarse to the touch. A slight stench can "+
     "be detected emanating from the blackened covers. A loose "+
     "page hangs out of the filthy book.\n");

  add_item(({ "stain", "stains" }),
     "Black, crusty stains not unlike dried blood.\n");
  add_item(({ "cover", "covers" }),
     "The covers appear to have been ruined by the smoke of a "+
     "fire. If this book had a title it has been totally lost "+
     "under the layers of grime.\n");
  add_item("grime",
     "Blood and fire have ruined this book's exterior.\n");
  add_item("page","@@page");

  add_prop(OBJ_I_WEIGHT, 1000);
  add_prop(OBJ_I_VOLUME, 1000);
  add_prop(OBJ_I_VALUE, 0);
}

string
page()
{
  reset_euid();
  cat("/d/Shire/khazad/obj/contents");
  return "";
}

int
read_book(string str)
{
  switch(str)
  {
    case "page 1" :
        reset_euid();
        cat("/d/Shire/khazad/obj/page1");
        return 1;
        break;
    case "page 2" :
        reset_euid();
        cat("/d/Shire/khazad/obj/page2");
        return 1;
        break;
    case "page 3" :
        reset_euid();
        cat("/d/Shire/khazad/obj/page3");
        return 1;
        break;
    default :
        notify_fail("Read which page?\n");
        return 0;
        break;
  }
}

init()
{
  ::init();
  add_action(read_book, "read");
}
