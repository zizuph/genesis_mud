/* The Master-object for Osgiliath
 * Elessar, Sep 94.
 */
inherit "/std/object";

#include <macros.h>
#include "/d/Gondor/defs.h"

#define MASTERFILE "/d/Gondor/anorien/osgiliath/obj/master"
#define GONDOR 0
#define MORDOR 1
#define BROKEN 0
#define REPAIRED 1

int ruler;
int wbridge, ebridge;

static object mleader, gleader;

void
create_object()
{
    if (IS_CLONE)
        return;

    set_short("The Master-object of the Osgiliath battles");
    set_long("This object is not supposed to be cloned.\n");
    FIX_EUID
}

set_ruler(int i)
{
  restore_object(MASTERFILE);
  ruler = i;
  save_object(MASTERFILE);
}

query_ruler()
{
  restore_object(MASTERFILE);
  return ruler;
}

set_ebridge_status(int i)
{
  ebridge = i;
  save_object(MASTERFILE);
}

query_ebridge_status() { restore_object(MASTERFILE); return ebridge; }

set_wbridge_status(int i)
{
  wbridge = i;
  save_object(MASTERFILE);
}

query_wbridge_status() { restore_object(MASTERFILE); return wbridge; }

set_mordor_leader(object ob)
{
  mleader = ob;
}

query_mordor_leader() { return mleader; }

set_gondor_leader(object ob)
{
  gleader = ob;
}

query_gondor_leader() { return gleader; }

