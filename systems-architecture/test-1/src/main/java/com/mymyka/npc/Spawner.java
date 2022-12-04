package com.mymyka.npc;

public class Spawner {
    public static void spawn(NPC npc) {
        System.out.println("--- Spawning: " + npc.getName() + " ---");
        npc.spawn();
        System.out.println("---------------------------------------");
    }
}
