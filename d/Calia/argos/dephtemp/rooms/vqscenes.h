/* Vision Quest Scenes
**
** The following declares and functions maintain the text of the
** historic scenes in
** the history of the Order of Dephonia which are needed to do the
** Vision of Delphia quest. Also included are functions which manipulate
** the information.
**
** History:
** Date       Coder      Action
** -------- ----------  -------------------------------------------
** 1/9/95   Zima        Created
**
*/
 
/*
**  vq_scene: an array of strings which contains the scenes found
**            on the tapestries matching those given during meditation
**            in the chapel
*/
string *vq_scene = ({
   "no scene 0",
   // 1 - found on a painting in room/quartch
      "the goddess Dephonia appearing to a group of astonished Argosians "+
      "who look rather dirty and worn out from work. Some look afraid "+
      "of the apparition while all have a look of non-recognition in "+
      "their eyes, as if they haven't seen such before",
 
   // 2 - tapestry found in rooms/classroom
      "the goddess Dephonia appearing to a haggered group of her followers " +
      "in a secluded dark room, their eyes filled with fear and then "  +
      "with joy at the appearance of their patroness",
 
   // 3 - a mural on the wall in rooms/dine2
      "a priestess kneeling dressed in a black robe wearing a gold "+
      "medallion, the goddess Dephonia standing over her with her hand "+
      "raised high as she pours oil from a vial over the priestess' head"+
      " while a great crowd looks on",
 
   // 4 - tapestry found in rooms/mstrnov
       "a Dephonian priestess, dressed " +
       "in a black tunic with a star-encircled raven, down on her " +
       "knees with her head lifted up, gazing into billowing clouds " +
       "which envelope a raven",
 
   //5 - sculpture on the wall in rooms/lounge
       "an elderly priestess dressed in her ceremonial robes bending "+
       "down before the goddess Dephonia as the deity places a "+
       "talisman around her neck",
 
   //6 - mural on wall in rooms/dine1
       "a great warrior bowing before the goddess Dephonia in a forest "+
       "as she presents him with an elaborate suit of gold armour and "+
       "a great sword",
 
   //7 - sculpture in rooms/corr28
       "a crowd of followers standing astonished in a forest as the "+
       "goddess Dephonia calls forth a beast from the woods, a muscular "+
       "giant with the head of a bull wielding a great axe",
 
   //8 - tapestry found in rooms/captngrd
      "a battle scene, in the midst "+
      "of which a warrior arrayed in elaborate armour is slaying " +
      "a regal figure who is falling from his winged steed. A " +
      "hideous creature which looks like a naked giant with a " +
      "bull's head gores the white steed, blood gushing forth " +
      "from both the steed and its rider",
 
   //9 - tapestry found in rooms/recept
      "a meeting across a long table, with armed military leaders " +
      "wearing armour cast with winged-steeds on one end, and " +
      "Dephonian priests adorned for battle on the other. The scene " +
      "seems to portray the signing of a treaty between the two "+
      "groups",
 
   //10 - mural in rooms/quartnps
      "the construction of a great temple in the woods, pillars being "+
      "erected by ropes around the walls of white marble",
 
   //11 - mural in rooms/quartnpr
      "the goddess Dephonia standing before the temple in the woods "+
      "surrounded a host of followers. The deity has her hands upraised "+
      "facing the white marble temple, which seems to be half-washed "+
      "in darkness",
 
   //12 - on ceiling in rooms/portico
      "the goddess Dephonia descending from the billowing clouds of "+
      "the sky, encircled by ravens in angelic postures",
 
   //13 - sculpture on wall in rooms/corr26
      "a prophetic vision of two high priests and a high priestess "+
      "of other cults bowing before the Hierophant of Dephonia "+
      "in honour and obedience"
});
 
/*
**  vq_prayer: an array of strings containing the prayers of honour
**             for each scene.
*/
string *vq_prayer = ({
      "no prayer 0.\n",
      "Empsanisae Protos",         // prayer 1
      "Elpida Progoni",            // prayer 2
      "Aleipso Delphia",           // prayer 3
      "Akoustico Opama",           // prayer 4
      "Mentagio Parousiasae",      // prayer 5
      "Palaekari Megalos",         // prayer 6
      "Ktaenos Skopos",            // prayer 7
      "Dogza Demonstrates",        // prayer 8
      "Suntheke Eirpun",           // prayer 9
      "Kataskeun Naos",            // prayer 10
      "Eulogia Naos",              // prayer 11
      "Pouli Agios",               // prayer 12
      "Thriambos Latreia"          // prayer 13
});
 
/*
**  vq_scene_short: an array of strings which are short descriptions
**                  of the scenes.
*/
string *vq_scene_short = ({
       "no short 0.\n",
       "the First Appearance of Our Mother",
       "the Visitation of Hope",
       "the Anointing of Delphia",
       "the Vision of Delphia",
       "the Presentation of the Talisman",
       "the Great Hero Demonstratus",
       "the Guardian",
       "the Death of Argos",
       "the Treaty of the Dark Woods",
       "the Construction of the Temple",
       "the Blessing of the Temple",
       "the Holy Angels",
       "the Triumph of the Order"
});
 
/*
** vq_scenekey: given a string name, returns the key selected for the
**              name, based on the second letter of the name
**              Provides a relationship between a player and WHICH
**              scene and prayer he/she uses to solve the quest.
**              Parameter: string name (of a player)
**              Returns:   integer scene key number
*/
int vq_scenekey(string name) {
   string key=(lower_case(extract(name,1,1)));
 
   switch (key) {
      case "a": case "b": return 1;
      case "c": case "d": return 2;
      case "e": case "f": return 3;
      case "g": case "h": return 4;
      case "i": case "j": return 5;
      case "k": case "l": return 6;
      case "m": case "n": return 7;
      case "o": case "p": return 8;
      case "q": case "r": return 9;
      case "s": case "t": return 10;
      case "u": case "v": return 11;
      case "w": case "x": return 12;
      case "y": case "z": return 13;
      default:            return 0;
   }
}
