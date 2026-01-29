/*
 * /d/Gondor/river/anduin/carrock2lorien/boatshelter.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * shelter of boatbuilder for the Beorning fishcamp
 *
 * TBD:
 * use search/take intercepts from carrock_cave
 * hide auger, mallet, saw, etc 
 */

#pragma strict_types

inherit "/d/Gondor/std/room";

#include "/d/Gondor/defs.h"
#include "fishcamp.h"

/* prototypes */
public void	create_gondor();
public void	reset_room();


/*
 * Function name:	create_gondor
 * Description	:	set up the shelter
 */
public void
create_gondor()
{
    FIX_EUID;   /* will be cloning objects */
    set_short("a shelter");
    set_long(BSN(
        "Stout timbers, grey and weathered, support a "+
        "lattice of lath and canvas overhead. A large chest "+
        "occupies the center of the shelter, "+
        "and various materials are piled around the edges."));
    
    add_exit((CARROCK_TO_LORIEN_DIR + "fishcamp_s"), "out", 0, 5, 1);
    add_exit((CARROCK_TO_LORIEN_DIR + "fishcamp_s"), "west", 0, 5, 1);

    add_item( ({ "shelter" }), long);
    add_item( ({ "supporting timber", "supporting timbers",
        "stout timber", "stout timbers", "timber", "timbers", }),
        BSN("The timbers are set deep in the sand, with stones heaped "+
            "around their bases. They have been worn grey and smooth by "+
            "weather."));
    add_item( ({ "timber base", "timbers bases", "base", "bases", }),
        BSN("The bases of the timbers are firmly buried deep in the sand, "+
        "and heaped 'round with smooth river stones."));
    add_item( ({ "smooth river stone", "smooth stone", "river stone", "stone",
        "smooth river stones", "smooth stones", "river stones", "stones", }),
        BSN("The stones are about fist-sized, smoothly rounded, and grey "+
            "or brown in colour."));
    add_item( ({ "sand", "ground" }),
        "The coarse sand underfoot is firmly packed.\n");

    add_item( ({ "lattice", }),
        BSN("Thin laths are interlaced overhead and topped with "+
            "a patched canvas.  The construction, when compared to the "+
            "supporting timbers, appears makeshift and flimsy."));
    add_item( ({ "construction", "roof" }),
        BSN("The lath and canvas provide some shelter from sun and "+
            "rain, but don't seem particularly sturdy."));
    add_item( ({ "thin lath", "thin laths", "lath", "laths", }),
        BSN("Thin laths of varying length and condition "+
            "are interlaced overhead to support the canvas. "+
            "They appear rather flimsy."));
    add_item( ({ "patched canvas", "faded canvas", "canvas", }),
        "The canvas is stretched across the lattice and tied "+
        "to the supporting timbers.  It has faded to a mottled white, "+
        "and is much patched.\n");
    add_item( ({ "patch", "patches" }),
        "Patches of varying size and age are stitched to the canvas.\n");

    add_item( ({ "pile", "piles", "edge", "edges",
        "materials", "material", "materials", }),
        BSN("Stacks of wood form waist-high walls around the edges "+
            "of the shelter. Buckets of varying sizes "+
            "sit atop the stacks, and detritus covers the ground "+
            "between."));
    add_item( ({ "waist-high wall", "waist-high walls", "wall", "walls", }),
        BSN("Stacks of wood, about waist-high, line the edges of "+
            "the shelter."));
    add_item( ({ "detritus", "junk" }),
        BSN("Rags, rusted bits of metal, scraps of wood and "+
            "the like are scattered around the shelter."));
    add_item( ({ "strips", "cloth", "rags" }),
        BSN("The rags are mere strips of cloth, paint-stained and "+
            "tattered. None appear of any use."));
    add_item( ({ "rusted bits of metal", "rusted bits", "rusted metal",
        "bits", "metal" }),
        BSN("The bits of metal are badly corroded; it is impossible "+
            "to determine their original function."));
    add_item( ({ "splinters", "splinter", "scrap of wood", "scraps of wood",
	"scrap", "scraps" }),
	BSN("Most of the scraps are little more than splinters."));
    add_item( ({ "stack of wood", "stack", "stacks of wood", "stacks",
        "wood", }),
        BSN("The stacks contain wood of all sizes. Some stacks appear "+
            "newly cut, but others are well-seasoned."));
    add_item( ({  "newly cut stack", "newly cut stacks", "newly cut wood",
    	"newer stack", "newer stacks", "newer wood", "new stack",
	"new stacks", "new wood", }),
        BSN("Some wood, still weeping green sap, appears to have been "+
        "cut only a few days ago."));
    add_item( ({  "older stack", "older stacks", "older wood",
	"old stack", "old stacks", "old wood", "well-seasoned stack",
	"well-seasoned stacks", "well-seasoned wood", }),
         BSN("The wood on the older stacks is darker in colour, "+
            "and quite dry."));
    add_item( ({ "fragrant sap", "green sap", "sap" }),
        "Fragrant sap oozes from the newly cut wood.\n");
    add_item( ({ "large bucket", "large buckets", "small bucket",
        "small buckets", "bucket", "buckets", }),
        BSN("The buckets are of wood, with rope handles. The larger ones "+
            "contain paint; the smaller contain some sticky resinous "+
            "substance."));
    add_item( ({ "rope", "rope handle", "rope handles", "handle", "handles" }),
        "The handles are just short lengths of rope.\n");
    add_item( ({ "paint" }),
        BSN("There are several buckets of grey paint, one of white, "+
            "and one of blue."));
    add_item( ({ "bucket of grey paint", "buckets of grey paint",
        "grey paint" }),
        "The paint is the grey of a November dawn.\n");
    add_item( ({ "white paint" }),
        BSN("The paint is a fairly clean white, with only a trace of "+
        "grey."));
    add_item( ({ "blue paint" }),
        "The paint is a deep blue, verging on black.\n");
    add_item( ({ "sticky resin", "sticky resinous substance",
        "sticky substance", "resinouse substance", "resin", "substance", }),
        BSN("The resin in the small buckets appears dense and quite "+
            "sticky."));

    add_cmd_item( ({ "stout timber", "stout timbers", "timber", "timbers", }),
        ({ "touch", "feel", }),
        "The timber, although unfinished, is fairly smooth to the touch.\n");
    add_cmd_item( ({ "newly cut stack", "newly cut stacks", "newly cut wood",
	"newer stack", "newer stacks", "newer wood", "new stack", "new stacks",
	"new wood", "fragrant sap", "green sap", "sap",}),
        ({ "smell", "sniff", }),
        BSN("The sap of the newly cut wood is redolent of sun-warmed forest."));
           
    reset_room();

} /* create_gondor */


/*
 * Function name:	reset_room
 * Description	:	be sure toolchest is here
 */
public void
reset_room()
{
    if (!objectp(present(CHEST_NAME, TO)))
    {
        clone_object(CHEST_FILE)->move(TO);
    }
} /* reset_room */
