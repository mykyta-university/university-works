package com.mymyka.main;

import com.mymyka.npc.*;

public class Main {
    public static void main(String[] args) {
        NPC bob = new TraderNPC("Bob");
        NPC roger = new TraderNPC("Roger");
        NPC steve = new TraderNPC("Steve");

        Spawner.spawn(bob);
        Spawner.spawn(roger);
        Spawner.spawn(steve);

        System.out.println("===========================");
        System.out.println("Some Event Happen");
        System.out.println("===========================");

        NPCDecorator snowBob = new SnowNPCDecorator(bob);
        NPCDecorator tradableRoger = new TradableNPCDecorator(roger);
        NPCDecorator snowTradableSteve = new TradableNPCDecorator(new SnowNPCDecorator(steve));

        Spawner.spawn(snowBob);
        Spawner.spawn(tradableRoger);
        Spawner.spawn(snowTradableSteve);
    }
}
