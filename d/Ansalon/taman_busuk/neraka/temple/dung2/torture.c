#pragma strict_types

#include "../defs.h"

inherit TEMPLE + "std_base.c";

void
create_temple_room()
{
    set_short("In a foul-smelling torture chamber");
    set_long("You are standing in a dimly lit circular chamber. Around " +
        "the walls you see various contraptions which are fairly large " +
        "in size. Two waist-high benches stand on the floor to one " +
        "side of the room and at the back of the room is a bed of " +
        "red-hot coals. Round patches of sawdust lie here and there on " +
        "the floor and just beside the entrance is a rack with all " +
        "kinds of pokers and pliers. Standing next to the rack is " +
        "a table on wheels with metal instruments laid out neatly in " +
        "a row on top of it. A couple of large metal cages hang from "+
	"the ceiling by heavy black chains.\n");

    add_item(({"chamber", "circular chamber"}),
        "This room has been carved straight out of the rock. It is of " +
        "a circular shape and the ceiling is domed giving no obvious " +
        "border between wall and ceiling.\n");

    add_item(({"wall", "walls", "rock"}),
        "The walls are carved from black rock streaked with dark-red " +
        "veins.\n");

    add_item(({"veins", "dark-red veins"}),
        "As you study the dark-red veins on the black rock wall, you " +
        "slowly realise that this is not the rock itself. The veins " +
        "seems to have been splashed on to the wall and run slowly " +
        "downwards. Here and there you notice that the veins are " +
        "a lighter colour of red and glistening with dampness.\n");

    add_item(({"dark-red veins", "dark veins"}), "As you study the " +
        "dark-red veins closely you see that they are not rock but " +
        "dried blood.\n");
    
    add_item(({"bench", "waist-high benches", "high benches", "benches"}),
        "There are two benches standing to one side of the room. \n");

    add_item(({"first bench", "wooden bench"}),
        "This wooden bench is solid and at the bottom end of it is an " +
        "iron bar which can be placed straight across the bench " +
        "and firmly secured with nuts and bolts. At the top end is " +
        "a large winch with a stained hemp rope around it.\n");

    add_item(({"bar", "iron bar"}),
        "It is about one inch thick, three inches wide, and as long as " +
        "the bench is wide. Along one side, evenly spaced, two " +
        "half-circular pieces have been cut out. You judge the size " +
        "to be about the size of your ankle. It is clear that this " +
        "bar is intended to be securely bolted across a person's lower " +
        "legs.\n");

    add_item(({"nuts", "bolts", "nuts and bolts"}),
        "Two thick iron nuts and bolts are used to secure the iron bar " +
        "to the wooden bench.\n");

    add_item(({"winch", "large winch"}),
        "This is a sturdy wooden winch placed at the top end of the " +
        "wooden bench. It has three handles which help to give a good " +
        "leverage when cranking the winch to tighten or loosen the " +
        "rope which is fastened to it.\n");

    add_item(({"handles"}),
        "The handles on the winch are made of wood and carved to give " +
        "a good grip. The wood has been stained dark by soot and " +
        "sweat.\n");

    add_item(({"rope", "hemp rope", "stained rope", "stained hemp rope"}),
        "This rope is fastened to the winch at the end of the bench. " +
        "The end of it is tied into a loop and it is stained by old " +
        "blood and sweat.\n");

    add_item(({"loop", "sticky loop"}),
        "This is clearly a loop to tie around someone's wrists.\n");

    add_item(({"second bench", "metal bench"}),
        "This is a metal bench consisting of a frame with rods across " +
        "it. Its legs have wheels fixed to them which makes it easy " +
        "to move.\n");

    add_item(({"frame", "iron frame"}),
        "This is a sturdy iron frame with iron rods across it.\n");

    add_item(({"rods", "iron rods"}),
        "These rods are one inch in diametre and placed with four " +
        "inches between eachother. They are securely fastened to " +
        "the frame and can carry quite a bit of weight.\n");

    add_item(({"legs", "legs on second bench", " iron legs"}),
        "The legs on this metal bench are made of iron as well. " +
        "Each leg has a wheel attached to it to make it easier to " +
        "move.\n");

    add_item(({"wheel", "wheels"}),
        "The wheels are made of iron.\n");

    add_item(({"bed", "bed of red-hot coals"}),
        "At the back of the room, sunk into the floor, is a large bed " +
        "of red-hot glowing coals. It is just about the same size as " +
        "the metal bench, only slightly smaller.\n");

    add_item(({"patch", "patches", "round patches", "sawdust"}),
        "Here and there on the floor you see patches of sawdust that " +
        "has been strewn on the floor. It has long lost the fresh " +
        "pale yellow colour of new sawdust as pools of blood have been " +
        "sucked up by it.\n");

    add_item(({"rack", "wooden rack"}),
        "This is a well-carved wooden rack for pokers and pliers. " +
        "There are also some hooks on it which have several different " +
        "types of whips hanging from them.\n");

    add_item(({"carving", "carvings"}),
        "As you look closer at the carvings on the rack you see that " +
        "here and there along the sides are little carved faces of " +
        "terrified people. Some of the faces are screaming in terror " +
        "while others have widened their eyes in silent fear.\n");

    add_item(({"poker", "pokers"}),
	"Standing in the rack are several pokers made of iron. They " +
        "vary in length and their handles are wrapped with leather " +
        "to give a good grip. Some of them have sharp pointed ends " +
        "while others are fairly blunt.\n");

    add_item(({"handle", "handles"}),
        "Narrow leather straps are wound around the handles of the " +
        "pokers to make them more comfortable to hold while using " +
        "them.\n");

    add_item(({"leather straps", "leather"}),
        "The leather is stained by sweat, soot, and vigorous use.\n");

    add_item(({"ends"}),
        "Which ends do you want to look at? The sharp ones or the " +
        "blunt ones?\n");

    add_item(({"sharp ends", "pointed ends", "sharp pointed ends"}),
        "They have been sharpened into a wicked point.\n");

    add_item(({"blunt ends"}),
        "It is hard to determine how these blunt pokers are supposed " +
        "to be use, but perhaps it is best not to dwell too much on " +
        "it. You see dried blood covering the end.\n");

    add_item(({"pliers"}),
        "Several iron pliers hang here. They are of various sizes and " +
        "some could be used to pull out teeth and others for pulling " +
        "out nails.\n");

    add_item(({"table"}),
        "This is a simple wooden table on wheels.\n");

    add_item(({"instruments"}),
        "On the table lie lots of various instruments of torture. " +
        "You see scoops, saws, drills, needles, and scalpels among " +
        "other things.\n");

    add_item(({"scoops"}),
        "These scoops look like scissors but instead of the blades " +
        "they have two half-sphere scoops. In one of them lies a " +
        "freshly plucked eye which shows you the use for them.\n");

    add_item(({"eye", "plucked eye", "freshly plucked eye"}),
        "It has been scooped out of someone's eyesocket.\n");

    add_item(({"saw", "saws"}),
        "There are a couple of saws lying on the table. They have " +
        "sharp teeth and along the edge you see fresh blood and " +
        "splinters of bone.\n");

    add_item(({"sharp teeth", "teeth"}),
        "The teeth on the saws are very sharp and you can understand " +
        "how they can grind through flesh and bone.\n");

    add_item(({"splinters", "splinters of bone", "bone"}),
        "Small splinters of newly sawed bone are wedged between the " +
        "teeth of the saw. Some small splinters lie on the table as " +
        "well.\n");

    add_item(({"fresh blood"}),
        "Fresh blood can be seen on several of the instruments in " +
        "this room.\n");

    add_item(({"blood"}),
        "Wherever you look in this room, you see traces of either " +
        "fresh or dried blood.\n");

    add_item(({"drills"}),
        "These drills are mate of metal with wooden handles. They are " +
        "bloody and a few strands of dark hair have been wound around " +
        "one drill.\n");

    add_item(({"needles", "sharp needles", "iron needles"}),
        "A set of ten sharp iron needles lie on the table.\n");

    add_item(({"scalpels", "blades"}),
        "There are three razor sharp scalpels lying on the table. " +
        "All of them have been wiped clean and the blades glimmer " +
        "red from the light from the bed of coals.\n");

    add_item(({"cages", "large metal cages", "large cages", "metal cages"}),
        "From the ceiling two large metal cages hang. They are both " +
        "the size of a man and the bars are about one inch thick " +
        "and three inches apart.\n");

    add_item(({"first cage"}),
        "You see a skull grinning back at you from the bottom of the " +
        "cage.\n");

    add_item(({"skull"}),
        "It is quite a small skull. Probably from a child or kender.\n");

    add_item(({"second cage"}),
        "Inside the second cage you see the lifeless form of a " +
        "kender.\n");

    add_item(({"chains", "black chains", "heavy chains", "heavy black chains"}),
        "The chains are made of black iron and the links look strong. " +
        "They run from the cages up to rings in the ceiling where they " +
        "are securely fastened.\n");

    add_item(({"rings", "rings in ceiling"}),
        "Two large iron rings protrude from the ceiling with chains " +
        "fastened to them.\n");


    add_cmd_item("veins", ({"touch", "feel"}), "There are different " +
        "types of veins to to touch. Please be more specific.\n");

    add_cmd_item(({"light veins", "light red veins", "glistening veins",
        "damp veins", "lighter red veins"}),
        ({"touch", "feel", "trace"}), "It is some kind of thick sticky " +
        "substance which has been splashed upon the wall and slowly " +
        "trickled down it creating a swirling pattern.\n");

    add_cmd_item(({"light veins", "light red veins", "glistening veins",
        "damp veins", "lighter red veins"}),
        "smell", "It smells like blood.\n");

    add_cmd_item(({"dark-red veins", "dark veins"}),
        ({"touch", "feel", "trace"}), "Youtrace a finger along a dark-red " +
        "vein and notice a little of it come off on your finger like " +
        "dried paint.n");

    add_cmd_item(({"dark-red veins", "dark veins"}),
        "smell", "You can't feel the smell of the dark veins. It must " +
        "be too faint.\n");

    add_cmd_item(({"rope", "hemp rope", "stained rope", "stained hemp rope"}),
        ({"touch", "feel"}), "The rope is rough and it is sticky " +
        "around the loop.\n");


    add_exit( DUNGTWO + "court.c", "south"); 
}



