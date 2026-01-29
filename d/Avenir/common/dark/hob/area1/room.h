// vim: filetype=lpc
#ifndef _AVE_AREA_HOBGOBLIN_
#define _AVE_AREA_HOBGOBLIN_
static void
config_random(void)
{
    shorts = ({
	"dead-end passage",
	"caved-in walkway",
	"collapsed passage",
    });

    long1 = ({
	"This is a branched walkway off the main corridor. Smaller "+
	   "in size, it quickly dead-ends, becoming choked off by "+
	   "fallen blocks of quartz and stone rubble.",
	"This is a caved-in side passage off the main corridor. It "+
	   "doesn't stretch very far, having collapsed by dint of its "+
	   "smaller size and lesser support.",
    });

    long2 = ({
	"Soot and filth make up the remainder of this rubble-filled "+
	   "stretch. Chipped and blackened blocks dislodged from the "+
	   "walls, floor and ceiling and scattered about, leaving "+
	   "various humps and hollows behind.",
	"Dislodged from the walls, floor and ceiling, various granite "+
	   "blocks, now blackened, are strewn about, forming a "+
	   "hazardous gauntlet of humps and hollows.",
    });

    long3 = ({
	"Evidence of occupation can been seen in the bits of scrap "+
	    "left lying about, alone and in clumps.",
	"Various bits of scrap and detritus are proof that this area "+
	    "undergoes occupation at least some of the time.",
    });

    extra_long = " Rusted iron sconces have been haphazardly attached "+
	"to the walls, providing light.";
}

static void
update_items(void)
{
    add_item(({"bits","scrap","scraps","detritus","clump","clumps"}),
	"Bits of scrap and detritus are scattered around the passage, "+
	"alone and in clumps, revealings signs of occupation.\n");
    add_item(({"scree","rubble", "stone rubble"}),
	"Scree and rubble of various size and quantity choke off "+
	"further access to the passageway, filling in around the "+
	"blocks and fallen stone.\n");
    add_item(({"shadow","shadows",}), "Shadows dance all along the "+
	"passage, obscuring the broken and pitted sufaces in areas.\n");
    add_item(({"sconce","sconces","iron sconce","iron sconces",
	"rusted sconce","rusted sconces"}), "The rusted iron sconces "+
	"are ubiquitous along the passage. Attached in haphazard "+
	"fashion, they hold a type of magikal torch that serves to "+
	"provide light.\n");
    add_item(({"light","torch","torches","wood","blackened wood"}),
	"Stout hafts of a blackened wood crowd the rusted iron sconces. "+
	"They emit a form of magikal light that is a bright, burning "+
	"orange with flickering bluish tips which throws light into "+
	"this small side-passage.\n");
    add_item(({"block","blocks","quartz", "quartz blocks"}),
	"Once majestic blocks of quartz used to form "+
	"the surface of the walls, floor and ceiling, deliving an "+
	"ensconced shining pathway through which to walk. Now though, "+
	"many are broken, shattered or dislodged and almost all are "+
	"entirely blackened.\n");
    add_item(({"hollow","hollows","earth",
	"bare earth"}), "Hollows of compacted, bare earth are visible in "+
	"those places where the quartz blocks are missing or shattered, "+
	"forming dangerous pitfalls which are sometimes obscured "+
	"by roving shadows.\n");
    add_item(({"hump","hump","stone","hard stone"}), "Evidence that "+
	"a great movement within the stone occured is apparent by the "+
	"rough, oblong protuberances of stone that bulge from the floor, "+
	"ceiling and walls. Dislodged quartz blocks lie about at random, "+
	"some broken, some whole, others shattered into rubble.\n");
    add_item(({"wall","walls","floor","ceiling"}), "The walls, floor and "+
	"ceiling are a patchwork mix of whole, broken or missing quartz "+
	"blocks.\n");
    add_item(({"corridor","main corridor"}),
	"The main corridor from which this passages branches off of is "+
	"larger and more strongly re-inforced against collapse unlike "+
	"here.\n");
    add_item(({"passage","passages","side passage","side passages",
	"section","sections"}), "You are standing in one!\n");
}

static void
update_noise(void)
{
    set_tell_time(200);

    add_tell("The sounds of scuffed footsteps echo into the area.");
    add_tell("Orange-blue light causes shadows to dance along the "+
	"passageway.");
    add_tell("A hoot.. or maybe a howl.. is reflected in from elsewhere.");
    add_tell("One of the magikal torches goes out.. and is re-ignited "+
	"a scant moment later.");
}

#endif /* _AVE_AREA_HOBGOBLIN_ */
