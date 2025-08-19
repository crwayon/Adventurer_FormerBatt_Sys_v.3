#include <iostream>
#include <string>
#include <thread>
#include <chrono>
using namespace std;

// 모험가 클래스
class Adventurer {
protected:
    int status[4];      // 스테이터스 배열 [HP, MP, 공격력, 방어력]
    int maxHP;          // 최대 HP
    int maxMP;          // 최대 MP
    int hpPotion;       // HP 포션 개수
    int mpPotion;       // MP 포션 개수
    string className;   // 직업명

public:
    Adventurer() {
        // 배열 초기화
        for (int i = 0; i < 4; i++) {
            status[i] = 0;
        }
        maxHP = 0;
        maxMP = 0;
        className = "모험가";
        // 포션 개수 초기화는 setPotion 함수에서 처리
    }

    virtual ~Adventurer() {}

    // 순수 가상 함수 - 모든 파생 클래스에서 반드시 구현해야 함
    virtual void attack() = 0;
    virtual void jobSkill() = 0;  // 전직 스킬 추가

    // 포션 개수 설정 함수 (Call by Pointer)
    void setPotion(int count, int* hpPotion, int* mpPotion) {
        *hpPotion = count;
        *mpPotion = count;
        this->hpPotion = *hpPotion;
        this->mpPotion = *mpPotion;
    }

    void initializeStats() {
        cout << "\n===============================================\n";
        cout << "       여신의 부름받아 TRPG세계에 강림\n";
        cout << "===============================================\n\n";

        // HP와 MP 입력
        cout << "[생명의 여신께서 마나와 생명을 부여합니다]\n\n";

        // HP 입력
        for (bool valid = false; !valid; ) {
            cout << "HP를 입력하세요: ";
            cin >> status[0];

            if (status[0] < 30 || status[0] > 50) {
                cout << "HP는 30 이상 50 이하여야 합니다.\n";
            }
            else {
                maxHP = status[0];  // 최대 HP 설정
                valid = true;
            }
        }

        // MP 입력 
        for (bool valid = false; !valid; ) {
            cout << "MP를 입력하세요: ";
            cin >> status[1];

            if (status[1] < 60 || status[1] > 70) {
                cout << "MP는 60 이상 70 이하여야 합니다.\n";
            }
            else {
                maxMP = status[1];  // 최대 MP 설정
                valid = true;
            }
        }

        cout << "\n[전쟁의 여신이 그대에게 용맹과 긍지를 부여합니다]\n\n";

        // 공격력 입력 (1 이상 50 이하)
        for (bool valid = false; !valid; ) {
            cout << "공격력을 입력하세요 (1~50): ";
            cin >> status[2];

            if (status[2] <= 0 || status[2] > 50) {
                cout << "공격력은 1 이상 50 이하여야 합니다.\n";
            }
            else {
                valid = true;
            }
        }

        // 방어력 입력 (1 이상 50 이하)
        for (bool valid = false; !valid; ) {
            cout << "방어력을 입력하세요 (1~50): ";
            cin >> status[3];

            if (status[3] <= 0 || status[3] > 50) {
                cout << "방어력은 1 이상 50 이하여야 합니다.\n";
            }
            else {
                valid = true;
            }
        }

        cout << "\n캐릭터 생성이 완료되었습니다!\n";

        // 포션 개수 설정 (5개씩)
        int hp = 5, mp = 5;
        setPotion(5, &hp, &mp);
    }

    // 전직 시 스탯 복사 함수
    void copyStats(Adventurer* source) {
        for (int i = 0; i < 4; i++) {
            this->status[i] = source->status[i];
        }
        this->maxHP = source->maxHP;
        this->maxMP = source->maxMP;
        this->hpPotion = source->hpPotion;
        this->mpPotion = source->mpPotion;
    }

    void showStatus() {
        cout << "\n┌─────────────────────────────────┐\n";
        cout << "│      현재 스테이터스            │\n";
        cout << "├─────────────────────────────────┤\n";
        cout << "│ 직업: " << className << "                    │\n";
        cout << "│ HP: " << status[0] << "/" << maxHP << "                    │\n";
        cout << "│ MP: " << status[1] << "/" << maxMP << "                    │\n";
        cout << "│ 공격력: " << status[2] << "                      │\n";
        cout << "│ 방어력: " << status[3] << "                      │\n";
        cout << "│ HP 포션: " << hpPotion << "개                   │\n";
        cout << "│ MP 포션: " << mpPotion << "개                   │\n";
        cout << "└─────────────────────────────────┘\n";
    }

    // 스탯 관리 시스템 - Pointer 사용
    void statManagementSystem(int* hp, int* mp, int* atk, int* def, int* hpPot, int* mpPot, int* maxHp, int* maxMp) {
        int choice;
        bool running = true;

        while (running) {
            cout << "\n===============================================\n";
            cout << "           <스탯 관리 시스템>\n";
            cout << "===============================================\n";
            cout << "1. HP 회복\n";
            cout << "2. MP 회복\n";
            cout << "3. HP 강화\n";
            cout << "4. MP 강화\n";
            cout << "5. 공격 스킬 사용\n";
            cout << "6. 전직 스킬 사용\n";
            cout << "7. 나가기\n";
            cout << "-----------------------------------------------\n";
            cout << "선택: ";
            cin >> choice;

            switch (choice) {
            case 1:  // HP 회복
                if (*hpPot > 0) {
                    int healAmount = 20;
                    if (*hp + healAmount > *maxHp) {
                        healAmount = *maxHp - *hp;
                    }
                    *hp += healAmount;
                    (*hpPot)--;
                    cout << "\n[HP가 " << healAmount << " 회복되었습니다. 포션이 1개 차감됩니다.]\n";
                    cout << "현재 HP: " << *hp << "/" << *maxHp << "\n";
                    cout << "남은 HP 포션: " << *hpPot << "개\n";
                }
                else {
                    cout << "\n[포션이 부족합니다.]\n";
                }
                break;

            case 2:  // MP 회복
                if (*mpPot > 0) {
                    int healAmount = 20;
                    if (*mp + healAmount > *maxMp) {
                        healAmount = *maxMp - *mp;
                    }
                    *mp += healAmount;
                    (*mpPot)--;
                    cout << "\n[MP가 " << healAmount << " 회복되었습니다. 포션이 1개 차감됩니다.]\n";
                    cout << "현재 MP: " << *mp << "/" << *maxMp << "\n";
                    cout << "남은 MP 포션: " << *mpPot << "개\n";
                }
                else {
                    cout << "\n[포션이 부족합니다.]\n";
                }
                break;

            case 3:  // HP 강화
                *hp *= 2;
                *maxHp *= 2;
                cout << "\n[HP가 2배로 증가되었습니다.]\n";
                cout << "현재 HP: " << *hp << "/" << *maxHp << "\n";
                break;

            case 4:  // MP 강화
                *mp *= 2;
                *maxMp *= 2;
                cout << "\n[MP가 2배로 증가되었습니다.]\n";
                cout << "현재 MP: " << *mp << "/" << *maxMp << "\n";
                break;

            case 5:  // 공격 스킬 사용
                if (*mp >= 50) 
                {
                    *mp -= 50;
                    cout << "\n[<스킬 이름> 사용하여 MP가 50 소모되었습니다.]\n";
                    cout << "현재 MP: " << *mp << "/" << *maxMp << "\n";
                    int reaction;
                    cin >> reaction;
                    if (reaction == 1) {
                        cout << "MP가 부족합니다! 필요 MP: 50\n";
                    }
                }
                else 
                {
                    cout << "\n[MP가 부족합니다! 필요 MP: 50]\n";
                }
                break;

            case 6:  // 전직 스킬 사용
                jobSkill();  // 각 직업별 고유 스킬 호출
                break;

            case 7:  // 나가기
                cout << "\n[이 세계를 구할 전설의 끝]\n";
                running = false;
                break;

            default:
                cout << "\n[반응을 선택하세요:]\n";
            }

            // 포인터를 통해 변경된 값을 멤버 변수에 동기화
            status[0] = *hp;
            status[1] = *mp;
            status[2] = *atk;
            status[3] = *def;
            hpPotion = *hpPot;
            mpPotion = *mpPot;
            maxHP = *maxHp;
            maxMP = *maxMp;
        }
    }

    // 오버로드된 스탯 관리 시스템 호출 함수
    void statManagementSystem() {
        // Pointer를 위해 포인터로 전달
        statManagementSystem(&status[0], &status[1], &status[2], &status[3], &hpPotion, &mpPotion, &maxHP, &maxMP);
    }

    string getClassName() { return className; }
};

// 용사 클래스
class Warrior : public Adventurer {
public:
    Warrior() {
        className = "용사";
    }

    // 전직 보너스 적용
    void applyJobBonus() {
        cout << "\n[용사 전직 보너스 적용!]\n";
        status[0] += 10;  // HP +10
        maxHP += 10;
        status[2] += 5;   // 공격력 +5
        cout << "HP +10, 공격력 +5 보너스를 받았습니다!\n";
    }

    // attack() 함수 오버라이딩
    void attack() override {
        cout << "\n[용사가 검을 휘둘러 강력한 일격을 가합니다!]\n";
        cout << "『슬래시!』 - 적에게 " << status[2] * 1.5 << "의 데미지를 입혔습니다!\n";
    }

    // 전직 스킬 오버라이딩
    void jobSkill() override {
        if (status[1] >= 30) {
            status[1] -= 30;
            cout << "\n[용사 전직 스킬 - 대검술!]\n";
            cout << "MP를 30 소비했습니다. (현재 MP: " << status[1] << "/" << maxMP << ")\n";
        }
        else {
            cout << "\n[MP가 부족합니다! 필요 MP: 30]\n";
        }
    }
};

// 드워프 클래스
class Dwarf : public Adventurer {
public:
    Dwarf() {
        className = "드워프";
    }

    // 전직 보너스 적용
    void applyJobBonus() {
        cout << "\n[드워프 전직 보너스 적용!]\n";
        status[0] += 5;   // HP +5
        maxHP += 5;
        status[3] += 10;  // 방어력 +10
        cout << "HP +5, 방어력 +10 보너스를 받았습니다!\n";
    }

    // attack() 함수 오버라이딩
    void attack() override {
        cout << "\n[드워프가 전투 도끼로 무거운 일격을 가합니다!]\n";
        cout << "『크러시!』 - 적에게 " << status[2] * 1.3 << "의 데미지를 입혔습니다!\n";
        cout << "대지가 울리는 강력한 일격!\n";
    }

    // 전직 스킬 오버라이딩
    void jobSkill() override {
        if (status[1] >= 25) {
            status[1] -= 25;
            cout << "\n[드워프 전직 스킬 - 대지의 일격!]\n";
            cout << "MP를 25 소비했습니다. (현재 MP: " << status[1] << "/" << maxMP << ")\n";
        }
        else {
            cout << "\n[MP가 부족합니다! 필요 MP: 25]\n";
        }
    }
};

// 현자 클래스
class Sage : public Adventurer {
public:
    Sage() {
        className = "현자";
    }

    // 전직 보너스 적용
    void applyJobBonus() {
        cout << "\n[현자 전직 보너스 적용!]\n";
        status[1] += 15;  // MP +15
        maxMP += 15;
        status[2] += 3;   // 공격력 +3
        cout << "MP +15, 공격력 +3 보너스를 받았습니다!\n";
    }

    // attack() 함수 오버라이딩
    void attack() override {
        cout << "\n[현자가 지팡이를 들어 마법을 시전합니다!]\n";
        cout << "『파이어볼!』 - 적에게 " << status[2] * 2 << "의 마법 데미지를 입혔습니다!\n";
        cout << "MP를 10 소비했습니다. (현재 MP: " << (status[1] - 10) << "/" << maxMP << ")\n";
        status[1] -= 10;
    }

    // 전직 스킬 오버라이딩
    void jobSkill() override {
        if (status[1] >= 40) {
            status[1] -= 40;
            cout << "\n[현자 전직 스킬 - 메테오!]\n";
            cout << "MP를 40 소비했습니다. (현재 MP: " << status[1] << "/" << maxMP << ")\n";
        }
        else {
            cout << "\n[MP가 부족합니다! 필요 MP: 40]\n";
        }
    }
};

// 메인 함수
int main() {
    // 기본 모험가로 초기 스탯 설정
    Adventurer* baseAdventurer = new Warrior();  // 임시 객체
    baseAdventurer->initializeStats();

    // 전직 시스템
    cout << "\n===============================================\n";
    cout << "           [전직 시스템]\n";
    cout << "===============================================\n";
    cout << "전직할 직업을 선택하세요:\n";
    cout << "1. 용사 (Warrior) - 강인한 체력과 용맹함\n";
    cout << "2. 드워프 (Dwarf) - 굴지의 장인정신\n";
    cout << "3. 현자 (Sage)  -  정제된 마나의 예리함\n";
    cout << "-----------------------------------------------\n";
    cout << "선택: ";

    int jobChoice;
    cin >> jobChoice;

    Adventurer* player = nullptr;

    // 선택에 따라 해당 직업 객체 생성 및 스탯 복사
    switch (jobChoice) {
    case 1: {
        Warrior* warrior = new Warrior();
        warrior->copyStats(baseAdventurer);  // 기본 스탯 복사
        warrior->applyJobBonus();  // 전직 보너스 적용
        player = warrior;
        cout << "\n[전직 완료!] 세기의 구원자! 용사!\n";
        break;
    }
    case 2: {
        Dwarf* dwarf = new Dwarf();
        dwarf->copyStats(baseAdventurer);  // 기본 스탯 복사
        dwarf->applyJobBonus();  // 전직 보너스 적용
        player = dwarf;
        cout << "\n[전직 완료!] 함성의 소리! 드워프!\n";
        break;
    }
    case 3: {
        Sage* sage = new Sage();
        sage->copyStats(baseAdventurer);  // 기본 스탯 복사
        sage->applyJobBonus();  // 전직 보너스 적용
        player = sage;
        cout << "\n[전직 완료!] 진리의 탐구! 현자!\n";
        break;
    }
    default: {
        cout << "\n[엇나간 선택] 용사로 전직합니다.\n";
        Warrior* warrior = new Warrior();
        warrior->copyStats(baseAdventurer);
        warrior->applyJobBonus();
        player = warrior;
    }
    }

    // 임시 객체 삭제
    delete baseAdventurer;

    // 전직 후 상태 표시
    player->showStatus();

    // 5초 후 전투 시스템으로 이동
    cout << "\n승리의 여신이 전장으로 안내합니다\n";
    for (int i = 5; i > 0; i--) {
        cout << i << "... ";
        cout.flush();
        this_thread::sleep_for(chrono::seconds(1));
    }

    // 전투 시스템
    cout << "\n\n===============================================\n";
    cout << "           [전투 시스템]\n";
    cout << "===============================================\n";
    cout << "진 : 뒤틀린 황천의 허수아비\n";

    // attack() 함수 호출하여 공격
    player->attack();

    // 전투 후 곧바로 스탯 관리 시스템으로 이동
    player->statManagementSystem();

    // 메모리 해제
    delete player;

    cout << "\n게임 종료\n";

    return 0;
}