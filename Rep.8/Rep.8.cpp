#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>


using namespace std;

struct Player {
    string name;
    string position;
    int goals;
    int matches;
    double averageRating;
};

void addPlayer(vector<Player>& team) {
    Player newPlayer;
    cout << "Введіть ім'я гравця: ";
    getline(cin, newPlayer.name);
    cout << "Введіть позицію гравця: ";
    getline(cin, newPlayer.position);
    cout << "Введіть кількість голів: ";
    cin >> newPlayer.goals;
    cout << "Введіть кількість матчів: ";
    cin >> newPlayer.matches;
    cout << "Введіть середній рейтинг: ";
    cin >> newPlayer.averageRating;

    team.push_back(newPlayer);
    cout << "Гравця успішно додано!\n";
}

void displayPlayers(const vector<Player>& team) {
    if (team.empty()) {
        cout << "Команда порожня.\n";
        return;
    }
    cout << "Ім'я"
        << "Позиція"
        << "Голи"
        << "Матчі"
        << "Рейтинг\n";
    cout << string(70, '-') << "\n";

    for (const auto& player : team) {
        cout << player.name
            << player.position
            << player.goals
            << player.matches
            << player.averageRating << "\n";
    }
}

void searchByPosition(const vector<Player>& team, const string& position) {
    cout << "Гравці на позиції \"" << position << "\":\n";
    bool found = false;
    for (const auto& player : team) {
        if (player.position == position) {
            cout << "- " << player.name << "\n";
            found = true;
        }
    }
    if (!found) {
        cout << "Гравців на цій позиції не знайдено.\n";
    }
}

int calculateTotalGoals(const vector<Player>& team) {
    int totalGoals = 0;
    for (const auto& player : team) {
        totalGoals += player.goals;
    }
    return totalGoals;
}

Player findTopScorer(const vector<Player>& team) {
    return *max_element(team.begin(), team.end(), [](const Player& a, const Player& b) {
        return a.goals < b.goals;
        });
}

Player findTopRatedPlayer(const vector<Player>& team) {
    return *max_element(team.begin(), team.end(), [](const Player& a, const Player& b) {
        return a.averageRating < b.averageRating;
        });
}

void formOptimalTeam(const vector<Player>& team, int maxPlayers) {
    vector<Player> sortedTeam = team;
    sort(sortedTeam.begin(), sortedTeam.end(), [](const Player& a, const Player& b) {
        return a.averageRating > b.averageRating;
        });

    cout << "Оптимальний склад команди (до " << maxPlayers << " гравців):\n";
    for (int i = 0; i < min(maxPlayers, (int)sortedTeam.size()); ++i) {
        cout << i + 1 << ". " << sortedTeam[i].name << " (Рейтинг: " << sortedTeam[i].averageRating << ")\n";
    }
}

void updatePlayer(vector<Player>& team, const string& name) {
    for (auto& player : team) {
        if (player.name == name) {
            cout << "Оновлюємо дані для гравця: " << player.name << "\n";
            cout << "Введіть нову кількість голів: ";
            cin >> player.goals;
            cout << "Введіть нову кількість матчів: ";
            cin >> player.matches;
            cout << "Введіть новий середній рейтинг: ";
            cin >> player.averageRating;
            cout << "Дані успішно оновлено!\n";
            return;
        }
    }
    cout << "Гравця з ім'ям \"" << name << "\" не знайдено.\n";
}

int main() {
    setlocale(0, ".1251");
    vector<Player> team;
    int choice;

    do {
        cout << "\nМеню:\n"
            << "1. Додати гравця\n"
            << "2. Вивести інформацію про гравців\n"
            << "3. Пошук гравців за позицією\n"
            << "4. Підрахувати загальну кількість голів\n"
            << "5. Знайти найкращого бомбардира\n"
            << "6. Знайти гравця з найвищим рейтингом\n"
            << "7. Формувати оптимальний склад\n"
            << "8. Оновити дані гравця\n"
            << "0. Вихід\n"
            << "Виберіть опцію: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addPlayer(team);
            break;
        case 2:
            displayPlayers(team);
            break;
        case 3: {
            cout << "Введіть позицію для пошуку: ";
            string position;
            cin.ignore();
            getline(cin, position);
            searchByPosition(team, position);
            break;
        }
        case 4:
            cout << "Загальна кількість голів: " << calculateTotalGoals(team) << "\n";
            break;
        case 5:
            if (!team.empty()) {
                Player topScorer = findTopScorer(team);
                cout << "Найкращий бомбардир: " << topScorer.name << " (Голи: " << topScorer.goals << ")\n";
            }
            else {
                cout << "Команда порожня.\n";
            }
            break;
        case 6:
            if (!team.empty()) {
                Player topRated = findTopRatedPlayer(team);
                cout << "Гравець з найвищим рейтингом: " << topRated.name << " (Рейтинг: " << topRated.averageRating << ")\n";
            }
            else {
                cout << "Команда порожня.\n";
            }
            break;
        case 7: {
            cout << "Введіть максимальну кількість гравців у складі: ";
            int maxPlayers;
            cin >> maxPlayers;
            formOptimalTeam(team, maxPlayers);
            break;
        }
        case 8: {
            cout << "Введіть ім'я гравця для оновлення: ";
            string name;
            cin.ignore();
            getline(cin, name);
            updatePlayer(team, name);
            break;
        }
        case 0:
            cout << "Вихід із програми.\n";
            break;
        default:
            cout << "Неправильний вибір. Спробуйте ще раз.\n";
        }
    } while (choice != 0);

    return 0;
}
