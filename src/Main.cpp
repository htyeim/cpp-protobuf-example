#include <iostream>
#include <fstream>
#include <stdexcept>
#include <myproto/Game.pb.h>

// using namespace std;
using namespace me::eax::examples::game;

void saveHero(const char* fname, const Hero& hero) {
    std::fstream out(fname, std::ios::out | std::ios::trunc | std::ios::binary);
    if(!hero.SerializeToOstream(&out))
        throw std::runtime_error("saveHero() failed");
}

void loadHero(const char* fname, Hero& hero) {        
    std::fstream in(fname, std::ios::in | std::ios::binary);
    if(!hero.ParseFromIstream(&in))
        throw std::runtime_error("loadHero() failed");
}

void printHero(const Hero& hero) {
    std::cout << "Name: " << hero.name() << std::endl;
    std::cout << "HP: " << hero.hp() << std::endl;
    std::cout << "XP: " << hero.xp() << std::endl;

    if(hero.has_mage_info()) {
        std::cout << "Class: mage" << std::endl;
        std::cout << "Spellbook: ";
        for(int i = 0; i < hero.mage_info().spellbook_size(); i++) {
            switch(hero.mage_info().spellbook(i)) {
                case Spell::FIREBALL:
                    std::cout << "fireball, ";
                    break;
                case Spell::THUNDERBOLT:
                    std::cout << "thunderbolt, ";
                    break;
                default:
                    std::cout << "(unknown spell), ";
                    break;
            }
        }
        std::cout << std::endl;
        std::cout << "Mana: " << hero.mage_info().mana() << std::endl;
    } else if(hero.has_warrior_info()) {
        std::cout << "Class: warrior" << std::endl;
        std::cout << "Weapon: " << (
                hero.warrior_info().weapon() == Weapon::SWORD ? "sword" :
                hero.warrior_info().weapon() == Weapon::BOW ? "bow" :
                "(unknown weapon)"
            ) << std::endl;
        std::cout << "Arrows: " << hero.warrior_info().arrows_number() << std::endl;
    } else {
        std::cout << "Class: (unknown class)" << std::endl;
    }

    std::cout << std::endl;
}

int main() {
    // Verify that the version of the library that we linked against is
    // compatible with the version of the headers we compiled against.
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    Hero warrior;
    warrior.set_name("eax");
    warrior.set_hp(50);
    warrior.set_xp(256);
    warrior.mutable_warrior_info()->set_weapon(Weapon::SWORD);
    warrior.mutable_warrior_info()->set_arrows_number(15);

    std::cout <<"SerializeToString start" <<std::endl;
    std::string output{};
    warrior.SerializeToString(&output);
    std::cout<<"SerializeToString: "<< output <<" "<<output.size() <<std::endl;
    for(auto const c:output){
        std::cout<<static_cast<int>(c)<<" ";
    }
    std::cout<<std::endl;
    Hero fromString;
    fromString.ParseFromString(output);
    printHero(fromString);
    std::cout<<"SerializeToString end"<<std::endl;

    Hero mage;
    mage.set_name("afiskon");
    mage.set_hp(25);
    mage.set_xp(1024);
    mage.mutable_mage_info()->add_spellbook(Spell::FIREBALL);
    mage.mutable_mage_info()->add_spellbook(Spell::THUNDERBOLT);
    mage.mutable_mage_info()->set_mana(100);

    std::cout << "Saving heroes..." << std::endl;
    saveHero("eax.dat", warrior);
    saveHero("afiskon.dat", mage);

    std::cout << "Loading heroes..." << std::endl;
    Hero warrior2;
    Hero mage2;
    loadHero("eax.dat", warrior2);
    loadHero("afiskon.dat", mage2);

    std::cout << std::endl;
    printHero(warrior2);
    printHero(mage2);
}

