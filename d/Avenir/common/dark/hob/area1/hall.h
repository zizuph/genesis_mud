// vim: filetype=lpc
#ifndef _AVE_AREA_HOBGOBLIN_
#define _AVE_AREA_HOBGOBLIN_
static void
config_random(void)
{
    shorts = ({
	"ancient corridor",
	"collapsing corridor",
	"segmented corridor",
    });

    long1 = ({
	"This is a segmented section of ancient corridor. A once grand "+
	   "stretch that is now broken, pitted.",
	"A ruined section of corridor, where once a grand hallway ran. "+
           "Now it is only a broken and pitted segmented stretch.",
    });

    long2 = ({
	"Once whole blocks of quartz used to form a smooth surface, but "+
	   "they are now chipped, blackened and scattered, leaving pitted "+
	   "hollows and ruptured bulges of hard stone.",
	"The surfaces of this area are a cavalcade of random pitfalls "+
	   "from broken and shattered quartz blocks which have come "+
	   "dislodged. Their now blackened majesty formerly providing "+
	   "safe cover.",
    });

    long3 = ({
	"Other sections of corridor branch off into myriad directions, "+
	   "some collapsed whilst others are awash in flickering light "+
	   "and dancing shadow.",
	"Shadows dance along the pitted surfaces in the flickering light. "+
	   "They also emit from the myriad side passages that "+
	   "branch off from this ancient main corridor.",
    });

    extra_long = " Rusted iron sconces have been haphazardly attached "+
	"to the walls, providing light.";
}

static void
update_items(void)
{
    add_item(({"shadow","shadows",}), "Shadows dance all along the "+
	"corridor, obscuring the broken and pitted sufaces in areas.\n");
    add_item(({"sconce","sconces","iron sconce","iron sconces",
	"rusted sconce","rusted sconces"}), "The rusted iron sconces "+
	"are ubiquitous along the corridor. Attached in haphazard "+
	"fashion, they hold a type of magikal torch that serves to "+
	"provide light.\n");
    add_item(({"light","torch","torches","wood","blackened wood"}),
	"Stout hafts of a blackened wood crowd the rusted iron sconces. "+
	"They emit a form of magikal light that is a bright, burning "+
	"orange with flickering bluish tips which throws light into the "+
	"disparate sections of corridor.\n");
    add_item(({"block","blocks","quartz", "quartz blocks"}),
	"Once majestic blocks of quartz used to form "+
	"the surface of the walls, floor and ceiling, deliving an "+
	"ensconced shining pathway through which to walk. Now though, "+
	"many are broken, shattered or dislodged and almost all are "+
	"entirely blackened.\n");
    add_item(({"pitfall","pitfalls","hollow","hollows","earth",
	"bare earth"}), "Hollows of compacted, bare earth are visible in "+
	"those places where the quartz blocks are missing or shattered, "+
	"forming dangerous pitfalls which are sometimes obscured "+
	"by roving shadows.\n");
    add_item(({"bulge","bulges","stone","hard stone"}), "Evidence that "+
	"a great movement within the stone occured is apparent by the "+
	"rough, oblong protuberances of stone that bulge from the floor, "+
	"ceiling and walls. Dislodged quartz blocks lie about at random, "+
	"some broken, some whole, others shattered into rubble.\n");
    add_item(({"wall","walls","floor","ceiling"}), "The walls, floor and "+
	"ceiling are a patchwork mix of whole, broken or missing quartz "+
	"blocks.\n");
    add_item(({"corridor","corridors","segment","segments",
	"hallway","hallways"}), "You are standing in it.\n");
    add_item(({"passage","passages","side passage","side passages",
	"section","sections"}), "Myriad side passages branch off from "+
	"this main corridor. They are smaller in girth and appear "+
	"no better off in state.\n");
}

static void
update_noise(void)
{
    set_tell_time(200);

    add_tell("The sounds of scuffed footsteps echo into the area.");
    add_tell("Orange-blue light causes shadows to dance along the "+
	"corridor.");
    add_tell("A hoot.. or maybe a howl.. is reflected in from elsewhere.");
    add_tell("One of the magikal torches goes out.. and is re-ignited "+
	"a scant moment later.");
}

#endif /* _AVE_AREA_HOBGOBLIN_ */
