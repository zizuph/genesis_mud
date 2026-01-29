// Standard asks and answers about the Gods of Sybarus.
// Inherit this into an npc and then do add_god_asks(); 
// inside the create_monster() func.
//
// YOU MUST ALSO create a set_default_answer(); or the
// ask will go unanswered.
//
// creator: Lilith, March-May 2022

inherit "/std/act/asking";

void
add_god_asks()
{
    add_ask(({"[about] [the] 'god' / 'gods' [of] [sybarus]"}),
        "say There are many gods in Sybarus. Some reign over Hours "+
        "and some do not.", 1);	
    add_ask(({"[about] [the] 'hours'"}),
        "say There are twelve hours in each day, and at least one god "+
        "is worshipped during that hour. Ask me about the first hour "+
        "if you want to know more.", 1);
    // First Hour
    add_ask(({"[about] [the] [god] / [gods] / [goddess] [of] [the] "+
        "'first' [hour]"}),
        "say Sair and Salilus are the Gods of the First Hour.", 1);
    add_ask(({"[about] [the] [god] / [goddess] 'sair'"}), 
        "say Sair is Goddess of the First Hour. She lends her "+
        "strength to walls and ceilings. Her symbol is the "+
        "octagon.", 1);
    add_ask(({"[about] [the] 'octagon' / 'octagons' [symbol]"}),
        "say The octagon is the symbol of Sair and you will see it "+
        "inscribed on many walls in Sybarus.", 1);
    add_ask(({"[about] [the] [god] / [goddess] 'salilus'"}), 
        "say Salilus is God of the First Hour. He opened the "+
        "way into the Sybarus cavern, that we might live under "+
        "the light of the Source. He is the god of doors and "+
        "portals, and his symbol is that of a lock and key.", 1);
    add_ask(({"[about] [the] 'lock' [and] 'key' [symbol]"}),
        "say The lock and key are symbolic of Salilus, God of the First "+
        "Hour. You will find his symbol in passages and doorways.", 1);		
    //Second Hour
    add_ask(({"[about] [the] [god] / [gods] / [goddess] [of] [the] "+
        "'second' [hour]"}), 
        "say The Second Hour is ruled by the conjoined gods "+
        "Tabris and Zeffar. Their symbol is that of a circle "+
		"halved by a lightning bolt. Together they govern aspects "+
        "of life involving Free Will and Irrevocable Choice.", 1);
    add_ask(({"[about] [the] 'circle' 'halved' [by] [a] "+
        "'lightning' 'bolt' [symbol]"}),
        "say Ah, yes, that is the symbol of the Second Hour and the "+
        "Gods Tabris-Zeffar.", 1);
    add_ask(({"[about] [the] [god] / [goddess] 'tabris'"}), 
        "say Tabris is the the brother of Zeffar. He is a god "+
        "of the Second Hour and governs Free Will.", 1);
    add_ask(({"[about] [the] [god] / [goddess] 'zeffar'"}), 
        "say Zeffar is the the brother of Tabris. He is a god "+
        "of the Second Hour and governs what we call irrevocable "+
        "choice: decisions that cannot be undone.", 1);
    // Third Hour		
    add_ask(({"[about] [the] [god] / [gods] / [goddess] [of] [the] "+
        "'third' [hour]"}), 
        "say Hahabi and his wife Mizrun are the gods of the Third "+
        "Hour. Their symbols are the red flame and the yellow "+
        "crescent.", 1);
    add_ask(({"[about] [the] [god] / [goddess] 'hahabi'"}), 
        "say Fear. Terror. Cowardice. These are the purvey of the "+
        "god Hababi. Some ask Him for relief from it. Others ask "+
        "Him to visit it upon their enemies during the Third Hour.", 1);
    add_ask(({"[about] [the] 'red' 'flame' [symbol]"}),
        "say The red flame is the symbol of Hababi, God of Terror "+
        "and Lord of the Third Hour.", 1);		
    add_ask(({"[about] [the] [god] / [goddess] 'mizrun' / 'misrun'"}),
        "say Mizrun, she is Goddess of the Third Hour. Her area "+
        "of influence is ignorance and forgetfulness, and the "+
        "unhappiness or bliss that accompanies them.", 1);
    add_ask(({"[about] [the] 'yellow' 'crescent' [symbol]"}),
        "say The yellow crescent is the symbol of Mizrun, who rules "+
        "over the Third Hour with Hahabi.", 1);		
    //Fourth Hour    		
    add_ask(({"[about] [the] [god] / [gods] / [goddess] [of] [the] " +
        "'fourth' [hour]"}), 
        "say Plalgus is God of the Fourth Hour. He is the judge of "+
        "all of us, from noble to slave.", 1);
    add_ask(({"[about] [the] [god] / [goddess] 'plalgus'"}), 
        "say Plalgus is God of the Fourth Hour. He is the judge of "+
        "all of us, from noble to slave. He is represented "+
        "with either of two symbols: a white eye, or a blue hammer.", 1);
    add_ask(({"[about] [the] 'white' 'eye' [symbol]"}),
        "say The White Eye of Plalgus sees all. He does not need sight "+
        "to know the truth, and judge accordingly.", 1);
    add_ask(({"[about] [the] [blue] 'hammer' [symbol]"}),
        "say The blue hammer is a symbol of Plalgus, or rather, of "+
        "being judged guilty by Plalgus.", 1);		
    //Fifth Hour		
    add_ask(({"[about] [the] [god] / [gods] / [goddess] [of] [the] " +
        "'fifth' [hour]"}), 
        "say The gods of the Fifth Hour are Nantur and her "+
        "husband, Thagrinus. They are often represented with "+
        "symbols of a quill pen and a black spot.", 1);
    add_ask(({"[about] [the] [god] / [goddess] 'nantur'"}), 
        "say Nantur is the goddess of knowledge. She is cold and "+
        "merciless in her quest for information, and this has "+
        "caused her followers much trouble over the years. Her "+
        "symbol is that of the quill pen. She is goddess of the "+
        "Fifth Hour.", 1);
    add_ask(({"[about] [the] 'quill' 'pen' [symbol]"}),
        "say Nantur is the goddess of knowledge. She is cold and "+
        "mericless in her quest for information, and this has "+
        "caused her followers much trouble over the years. Her "+
        "symbol is that of the quill pen. She is goddess of the "+
        "Fifth Hour.", 1);
    add_ask(({"[about] [the] [god] / [goddess] 'thagrinus'"}), 
        "say God of the Fifth Hour, Thagrinus reigns over "+
        "confusion, distraction, and complexity. His symbol is "+
		"a simple black spot.", 1);
    add_ask(({"[about] [the] 'black 'spot' [symbol]"}), 
        "say God of the Fifth Hour, Thagrinus reigns over "+
        "confusion, distraction, and complexity. His symbol is "+
		"a simple black spot.", 1);
    // Sixth Hour
    add_ask(({"[about] [the] [god] / [gods] / [goddess] [of] [the] " +
        "'sixth' [hour]"}), "say Nitikas and Zahun rule over the "+
        "Sixth Hour.", 1);
    add_ask(({"[about] [the] [god] / [goddess] 'nitikas'"}), 
        "say Nitikas is god of wealth and greed. He is a god of "+
        "the Sixth Hour and his symbol is a coin.", 1);
    add_ask(({"[about] [the] 'coin' [symbol]"}),		
        "say Nitikas is god of wealth and greed. He is a god of "+
        "the Sixth Hour and his symbol is a coin.", 1);	
    add_ask(({"[about] [the] [god] / [goddess] 'zahun'"}), 
        "say Zahun is the goddess of the Sixth Hour. She delights "+
        "in scandal and intrigue and her symbol is that of a "+
        "circle divided by a cross.", 1);
    add_ask(({"[about] [the] 'cross' [symbol]"}),
        "say Zahun is the goddess of the Sixth Hour. She delights "+
        "in scandal and intrigue and her symbol is that of a "+
        "circle divided by a cross.", 1);	
    // Seventh Hour
    add_ask(({"[about] [the] [god] / [gods] / [goddess] [of] [the] " +
        "'seventh' [hour]"}), "say The gods of the Seventh Hour "+
        "are Cahor and Tarob.", 1);
    add_ask(({"[about] [the] [god] / [goddess] 'cahor'"}), 
        "say Goddess of the Fourth Hour, Cahor's sphere of "+
        "influence is deception, illusion, and delusion. She "+
		"is often represented by the symbol of two linked "+
        "circles.", 1);
    add_ask(({"[about] [the] 'two' 'linked' 'circles' [symbol]"}),
        "say Goddess of the Fourth Hour, Cahor's sphere of "+
        "influence is deception, illusion, and delusion. She "+
		"is often represented by the symbol of two linked "+
        "circles.", 1);    	
    add_ask(({"[about] [the] [god] / [goddess] 'tarob'"}), 
        "say Tarob? He is God of the Seventh Hour. He's not "+
        "one you want to be on the wrong side of. He delights in "+
        "extortion, coercion, and oppression. His sincerest "+
        "followers are thought to be immune to such tactics "+
        "whilst also being practitioners of them. His symbol "+
        "is a knife.", 1);
    add_ask(({"[about] [the] 'knife' [symbol]"}),
        "say The knife is a complex symbol. It is claimed by "+
        "Tarob, the god of the Seventh Hour who sees it as a "+
        "tool of extortion, and by the Shadow Union, who view "+
        "it as a tool of death for those who fail to heed the "+
        "laws of Sybarus.", 1);
    // Eighth Hour
    add_ask(({"[about] [the] [god] / [gods] / [goddess] [of] [the] " +
        "'eighth' [hour]"}), 
        "say The Eighth Hour is ruled by Tacritan and Zizuph", 1);
    add_ask(({"[about] [the] [god] / [goddess] 'tacritan'"}), 
        "say Tacritan is the god of sorcery and the one who "+
        "bestows magic to mortal magi. His symbol is that of "+
        "a translucent orb. He rules over the Eighth Hour with "+
        "Zizuph.", 1);
    add_ask(({"[about] [the] [translucent] 'orb' [symbol]"}),
        "say The translucent orb is the symbol of Tacrican, "+
        "God of sorcery and of the Eighth Hour.", 1);		
    add_ask(({"[about] [the] [god] / [goddess] 'zizuph'"}), 
        "say We do not know the gender of Zizuph, The Is of "+
        "Mysteries. We know only that Zizuph is the veil through "+
        "which The Divine is experienced, the conduit through "+
        "which clerics attain their powers. Zizuph's symbol "+
		"is that of a veil, or a blue teardrop.", 1);
    add_ask(({"[about] [the] [blue] 'veil' / 'teardrop' [symbol]"}),
        "say The veil and the blue teardrop are both symbols of "+
        "Zizuph, the Is of Mysteries, who reigns over the "+
	    "Eighth Hour with Tacritan.", 1);			
    // Ninth Hour
    add_ask(({"[about] [the] [god] / [gods] / [goddess] [of] [the] " +
        "'ninth' [hour]"}), 
        "say Zaren, Goddess of Wrath, has "+
        "the Ninth Hour all to herself. Hers is the sphere of "+
        "righteous anger and divine punishment. Those who come "+
        "to Her through Plalgus know great suffering before "+
        "Mascarvin claims them. Her symbol is a closed fist.", 1);
    add_ask(({"[about] [the] [god] / [goddess] 'zaren'"}),	
        "say Zaren, Goddess of Wrath, has "+
        "the Ninth Hour all to herself. Hers is the sphere of "+
        "righteous anger and divine punishment. Those who come "+
        "to Her through Plalgus know great suffering before "+
        "Mascarvin claims them. Her symbol is a closed fist.", 1);	
    add_ask(({"[about] [the] 'closed' 'fist' [symbol]"}),
        "say The closed fist is the symbol of Zaren, Goddess of "+
        "the Ninth Hour. All tremble before her wrath.", 1);
    // Tenth Hour
    add_ask(({"[about] [the] [god] / [gods] / [goddess] [of] [the] " +
        "'tenth' [hour]"}), 
        "say Sabrus, She Who Sustains Us, is the Goddess of the "+
        "Tenth Hour. She is the daughter of Sachluph and Hizarbin. "+
        "Through her, we are provided sustenance to fulfill "+
        "our duties to Sybarus. The rectangle symbolizing a loaf "+
        "of bread is sacred to Her.", 1);
    add_ask(({"[about] [the] [god] / [goddess] 'sabrus'"}),
        "say Sabrus, She Who Sustains Us, is the Goddess of the "+
        "Tenth Hour. She is the daughter of Sachluph and Hizarbin. "+
        "Through her, we are provided sustenance to fulfill "+
        "our duties to Sybarus. The rectangle symbolizing a loaf "+
        "of bread is sacred to Her.", 1);
    add_ask(({"[about] [the] 'loaf' / 'rectangle' [symbol]"}),
        "say The rectangle or loaf-shaped symbol is sacred to Sabrus "+
        "who is the Goddess of the Tenth Hour.", 1);		
    // Eleventh Hour
    add_ask(({"[about] [the] [god] / [gods] / [goddess] [of] [the] " +
        "'eleventh' [hour]"}), 
        "say Hizarbin and Sachluph are the Gods of the Eleventh "+
        "Hour. Hizarbin is the Lord of the Waters and Sachluph "+
        "governs plants, and the poultices and poisons that "+
        "arise from them.", 1);
    add_ask(({"[about] [the] [god] / [goddess] 'hizarbin'"}), 
        "say Hizarbin is Lord of the Waters, God of the Eleventh "+
        "Hour.  His symbol is that of a wavy line. If you see "+
        "three wavy lines that is a summoning of Him.", 1);
    add_ask(({"[about] [the] 'wavy' 'line' [symbol]"}),
    	"say Hizarbin is Lord of the Waters, God of the Eleventh "+
        "Hour.  His symbol is that of a wavy line. If you see "+
        "three wavy lines that is a summoning of Him.", 1);
    add_ask(({"[about] [the] [god] / [goddess] 'sachluph'"}), 
        "say Sachluph is the Goddess of Plants and the Eleventh "+
        "Hour. For Her, all plants flower and give up their "+
        "secret powers. Her symbol is a willow wand entwined with "+
        "serpents.", 1);
    add_ask(({"[about] [the] 'willow' 'wand' [entwined] [with] "+
	    "[serpents] [symbol]"}),
        "say Sachluph is the Goddess of Plants and the Eleventh "+
        "Hour. For Her, all plants flower and give up their "+
        "secret powers. Her symbol is a willow wand entwined with "+
        "serpents.", 1);
    // Twelfth Hour   
    add_ask(({"[about] [the] [god] / [gods] / [goddess] [of] [the] " +
        "'twelfth' / 'twelvth' [hour]"}), 
        "say Surely you know that Jazur and her husband Sisera "+
        "are the Gods of the Twelfth Hour! They reign over "+
        "Passion and Pleasure.", 1);
    add_ask(({"[about] [the] [god] / [goddess] 'jazur'"}), 
        "say Jazur embodies Passion. She unifies sybarites through "+
        "collecting our emotions -- our devotion, our ecstacy, and "+
        "our suffering -- into a massive Flame that burns strong so "+
        "long as we make offerings to Her. Her symbol, of course, is "+
        "an eternal flame, blue-black in colour. She is at the height "+
        "of her Power during the Twelfth Hour.", 1);
    add_ask(({"[about] [the] [eternal] [black] / [blue] / [blue-black] "+
        "'flame' [symbol]"}),
        "say The blue or black flame symbol is sacred to Jazur, "+
        "Goddess of Passion. "+
        "When depicted with Sisera, you'll often see a black "+
        "triangle with the point down representing Her.", 1);
    add_ask(({"[about] [the] 'black' 'triangle' [symbol]"}),
        "say The black triangle represents Jazur when it is paired "+
        "above a red triangle, for Sisera.", 1);        
	add_ask(({"[about] [the] [god] / [goddess] 'sisera'"}), 
        "say Quite the charmer, Sisera is. He's the God of Pleasure "+
        "and not just the simple ones, mind you. He's Jazur's "+
        "mate and to match her Passion, he's got to be ever at "+
        "the ready, if you get my meaning. His symbol is a red "+
		"triangle, pointed up.", 1);
    add_ask(({"[about] [the] 'red' 'triangle' [symbol]"}),
        "say The red triangle represents Sisera, God of Pleasure, "+
        "who reigns over the Twelfth Hour.", 1);
	// Other Gods	
    add_ask(({"[about] [the] [god] / [goddess] 'aclolthayr' / "+ 
	    "'lolth'"}), "say The spider Goddess, she is. Goddess of "+
		"the Hunt and of Sport. When you see a spider or a spiral "+
		"you'll know its about Aclolthayr -- so take care. She "+
        "likes to play with Her food.", 1);
    add_ask(({"[about] [the] 'spider' / 'spiral' [symbol]"}),
        "say The symbol of Aclolthayr, that is. When you see it, "+
        "take care. She and her followers will make your death "+
        "their sport.", 1);		
    add_ask(({"[about] [the] [god] / [goddess] 'alphum'"}), 
        "say He's a gentle, peaceful sort, is Alphum. He keeps "+
        "the Calm here in Sybarus, as best he can. His symbol "+
        "is a dove.", 1);
    add_ask(({"[about] [the] 'dove' [symbol]"}),
        "say That's the symbol of Alphum, God of Peace.", 1);	
    add_ask(({"[about] [the] [god] / [goddess] 'azauph' / "+
        "'azeuph'"}), "say She's the daughter of Mascarvin. "+
        "say Goddess of maternity, children, and the like. Sad "+
        "thing about what happened to her daughter Tjana. "+
        "She's crazy-mad at Nitikas so if you see them in "+
        "the same place, move fast. Her symbol is a cradle.", 1);
    add_ask(({"[about] [the] 'cradle' [symbol]"}),
        "say A cradle is the symbol of the goddess Azauph.", 1);		
    add_ask(({"[about] [the] [god] / [goddess] 'bucaphi'"}), 
        "say Bucaphi is the god of music, entertainment, and "+
        "revelry. Everyone loves Bucaphi. His symbol is a flute.", 1);
    add_ask(({"[about] [the] 'flute' / 'music' [symbol]"}),
        "say The flute is the symbol of the God Bucaphi, "+
        "god of music and merrymaking.", 1);
    add_ask(({"[about] [the] [god] / [goddess] 'mascarvin'"}), 
        "say Mascarvin is the Goddess of Death and Rebirth. "+
        "She gathers us up when we die and it is She who "+
        "decides when we may be reborn. Her symbol is a "+
        "grinning skull.", 1);
    add_ask(({"[about] [the] [grinning] 'skull' [symbol]"}),
        "say That be the symbol of Mascarvin.", 1);	
    add_ask(({"[about] [the] [god] / [goddess] 'schlachlil'"}), 
        "say Some assume Schlachlil is male but that God "+
        "only manifests as the Light of the Source, so "+
        "who knows? What we all know though, is that without "+
        "Schlachlil, Sybarus would be in darkness. The "+
        "symbol of Schlachlil is a crystal shard.", 1);
    add_ask(({"[about] [the] 'crystal' 'shard' [symbol]"}),
	    "say If you see a crystal shard drawn somewhere "+
        "or maybe a shard of crystal on a pedestal, it is "+
        "meant as a symbol of the god Schlachlil.", 1);    
    add_ask(({"[about] 'tjana'"}), "say She was the daughter "+
        "of Azauph and a High Lord. Nitikas coveted her for "+
        "her beauty and when she refused his advances, he "+
        "turned her into a statue--which broke when Azauph "+
        "fought with him to get her back. Supposedly Azauph "+
        "is still looking for the last pieces.", 1);
}	