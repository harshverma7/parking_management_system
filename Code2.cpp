#include <bits/stdc++.h>
using namespace std;
class parking_system
{
public:
    int no_parking_slots;
    int no_interconnected_slots;
    int source;
    vector<bool> visited_parking_slots;
    vector<pair<int, int> > dist_src_index;

    void get_slots_info()
    {
        cout << "Enter the number of parking slots: ";
        cin >> no_parking_slots;
        cout << "Enter the number of interconnected parking slots: ";
        cin >> no_interconnected_slots;
        // Taking source as 0
        source = 0;
    }

    void get_parking_details()
    {
        // Creating parking slots by the admin
        int first_point, second_point, distance;
        vector<pair<int, int> > g[no_parking_slots + 1]; // doubt

        // Creating the adjacency list of the graph
        cout << "\nTREATING ENTRY POINT AS 0 ENTER THE DETAIL AS FOLLOWS----->";
        for (int i = 0; i < no_interconnected_slots; i++)
        {
            cout << "\nEnter the first point: ";
            cin >> first_point;
            cout << "\nEnter the second point: ";
            cin >> second_point;
            cout << "\nEnter the distance between the two points in meters: ";
            cin >> distance;
            g[first_point].push_back(make_pair(second_point, distance)); //doubt
            g[second_point].push_back(make_pair(first_point, distance)); //doubt
        }
        // Dijkstra's algorithm begins from here
        priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq; //doubt from here
        vector<int> distTo(no_parking_slots + 1, INT_MAX);
        distTo[source] = 0;
        pq.push(make_pair(0, source));

        while (!pq.empty())
        {
            int dist = pq.top().first;
            int prev = pq.top().second;
            pq.pop();
            vector<pair<int, int> >::iterator it;
            for (it = g[prev].begin(); it != g[prev].end(); it++)
            {
                int next = it->first;
                int nextDist = it->second;
                if (distTo[next] > distTo[prev] + nextDist)
                {
                    distTo[next] = distTo[prev] + nextDist;
                    pq.push(make_pair(distTo[next], next));
                }
            }
        } // doubt till here
        // Dijkstra's algorithm ends here 

        // Storing the distance of the source from all the parking slots and its index
        for (int i = 1; i <= no_parking_slots; i++)
        {
            dist_src_index.push_back(make_pair(distTo[i], i));
        }

        // sorting the distance of the source from all the parking slots
        sort(dist_src_index.begin(), dist_src_index.end());

        // Creating a boolean vector to check if the parking slot is visited or not
        for (int i = 0; i < no_parking_slots + 1; i++)
        {
            visited_parking_slots.push_back(false);
        }
        cout << "\nParking slots added successfully\n";
    }

    int get_parking_status()
    {
        int count_empty_slots = 0;
        for (int i = 0; i < no_parking_slots; i++)
        {
            if (visited_parking_slots[dist_src_index[i].second] == false)
            {
                count_empty_slots++;
            }
        }
        return count_empty_slots;
    }
};
parking_system p;
class parking_allocation
{
public:
    char name[100];
    long long int phone_number;
    char vehicle_number[100];
    char email[100];
    int allotted_parking_slot_number;
    int token_number_entry;
    int entry_time;
    int alloting_parking_slot()
    {
        // cout<<p.visited_parking_slots[p.dist_src_index[0].second];
        int empty_slots = p.get_parking_status();
        int allotted_slot;
        // Getting the number of empty parking slots
        if (empty_slots == 0)
        {
            // cout << "\nSorry, no parking slots are available";
            allotted_slot = -1;
        }
        else
        {
            for (int i = 0; i < p.dist_src_index.size(); i++)
            {
                if (p.visited_parking_slots[p.dist_src_index[i].second] == false)
                {
                    // cout << "\nThe parking slot allocated to you is: " << p.dist_src_index[i].second;
                    allotted_slot = p.dist_src_index[i].second;
                    p.visited_parking_slots[p.dist_src_index[i].second] = true;
                    break;
                }
            }
        }
        return allotted_slot;
    }
    int token_number_generator()
    {
        int token_number_int = 0;
        int token_number[100];
        for (int i = 0; i < 3; i++)
        {
            token_number[i] = rand() % 10 + '0';
            token_number_int = token_number_int * 10 + (token_number[i] - '0');
        }
        return token_number_int;
    }
    // Getting personal details of the user
    void get_personal_info()
    {
        cout << "\nEnter the name: ";
        cin >> name;
        cout << "\nEnter the phone number: ";
        cin >> phone_number;
        cout << "\nEnter the email: ";
        cin >> email;
        cout << "\nEnter the vehicle number: ";
        cin >> vehicle_number;
        cout << "\nEnter the time in which you entered the parking area in 24 hours format: ";
        cin >> entry_time;
    }

    // Allotting nearest parking slot to the user

    // Displaying the details of the user
    void display_user_info()
    {
        cout << "\n";
        cout << "\nName: " << name;
        cout << "\nPhone number: " << phone_number;
        cout << "\nEmail: " << email;
        cout << "\nVehicle number: " << vehicle_number;
        cout << "\nParking slot number: " << allotted_parking_slot_number;
        cout << "\nYour entry time is: " << entry_time << " hours";
        cout << "\nYour Token number: " << token_number_entry << "\n";
    }
};
parking_allocation p_a;
class parking_slot_vacation
{
public:
    char name[100];
    long long int phone_number;
    char vehicle_number[100];
    char email[100];
    int allotted_parking_slot_number;
    int token_number_exit;
    int exit_time;
    int total_parking_fare;

    void get_token_number()
    {
        cout << "\nEnter your token number: ";
        cin >> token_number_exit;
    }
    void get_exit_time()
    {
        cout << "\nEnter the time in which you exited the parking area in 24 hours format: ";
        cin >> exit_time;
    }
    void update_parking_detail()
    {
        p.visited_parking_slots[allotted_parking_slot_number] = false;
    }

    void parking_fare()
    {
        total_parking_fare = 0;
        int parking_time;
        parking_time = exit_time - p_a.entry_time;
        if (parking_time >= 0 && parking_time <= 3)
        {
            total_parking_fare = 100;
        }
        else if (parking_time > 3 && parking_time <= 6)
        {
            total_parking_fare = 200;
        }
        else if (parking_time > 6 && parking_time <= 9)
        {
            total_parking_fare = 300;
        }
        else if (parking_time > 9 && parking_time <= 12)
        {
            total_parking_fare = 400;
        }
        else if (parking_time > 12 && parking_time <= 15)
        {
            total_parking_fare = 500;
        }
        else if (parking_time > 15 && parking_time <= 18)
        {
            total_parking_fare = 600;
        }
        else if (parking_time > 18 && parking_time <= 21)
        {
            total_parking_fare = 700;
        }
        else if (parking_time > 21 && parking_time <= 24)
        {
            total_parking_fare = 800;
        }
    }
    void user_info_exit()
    {
        cout << "\nYour Details: ";
        cout << "\nName: " << name;
        cout << "\nPhone number: " << phone_number;
        cout << "\nEmail: " << email;
        cout << "\nVehicle number: " << vehicle_number;
        cout << "\nParking slot number: " << allotted_parking_slot_number;
        cout << "\nYour exit time is: " << exit_time << " hours";
        parking_fare();
        cout << "\nYour parking fare is: " << total_parking_fare;
    }
};
class user_details
{
public:
    char name[100];
    long long int phone_number;
    char vehicle_number[100];
    char email[100];
    int allotted_parking_slot_number;
    int token_number_entry;
    int entry_time;
    void dis_ud_admin()
    {
        cout << "\n";
        cout << "\nDetails of the user are as follows\n";
        cout << "\nName: " << name;
        cout << "\nPhone number: " << phone_number;
        cout << "\nEmail: " << email;
        cout << "\nVehicle number: " << vehicle_number;
        cout << "\nParking slot number: " << allotted_parking_slot_number;
        cout << "\nYour entry time is: " << entry_time << " hours";
        cout << "\nYour Token number: " << token_number_entry << "\n";
    }
};
user_details u_d;
parking_slot_vacation p_s_v;
class user
{
public:
    void user_menu()
    {
        int choice;
        fstream f;
        f.open("user_details.txt", ios::in | ios::out | ios::binary);
        do
        {
            cout << "\nUser Menu\n";
            cout << "\n1. Enter the parking area\n";
            cout << "\n2. Exit the parking area\n";
            cout << "\n3. Exit\n";
            cout << "\nEnter your choice: ";
            cin >> choice;
            p_a.allotted_parking_slot_number = p_a.alloting_parking_slot();
            switch (choice)
            {
            case 1:
                if (p_a.allotted_parking_slot_number == -1)
                {
                    cout << "\nSorry, no parking slot is available.\n";
                }
                else
                {
                    p_a.token_number_entry = p_a.token_number_generator();
                    p_a.get_personal_info();
                    f.write((char *)&p_a, sizeof(p_a));
                    p_a.display_user_info();
                }
                break;
            case 2:
                p_s_v.get_token_number();
                f.seekg(0);
                while (f.read((char *)&p_a, sizeof(p_a)))
                {
                    if (p_a.token_number_entry == p_s_v.token_number_exit)
                    {
                        strcpy(p_s_v.name, p_a.name);
                        p_s_v.phone_number = p_a.phone_number;
                        strcpy(p_s_v.vehicle_number, p_a.vehicle_number);
                        strcpy(p_s_v.email, p_a.email);
                        p_s_v.allotted_parking_slot_number = p_a.allotted_parking_slot_number;
                        p_s_v.get_exit_time();
                        p_s_v.user_info_exit();
                        p_s_v.update_parking_detail();
                        p_s_v.user_info_exit();
                        cout << "\nThank you for using our services\n";
                    }
                    break;
                }
                break;
            case 3:
                break;
            default:
                cout << "\nInvalid choice\n";
            }
        } while (choice != 3);
        f.close();
  }
};
user u;
class admin
{
public:
    char password[100];
    int empty_slots;
    char pass[10] = "admin";
    int choice;
    void admin_menu()
    {
        cout << "\nEnter the password: ";
        cin >> password;
        if (strcmp(pass, password) == 0)
        {
            cout << "\nAccess granted";
            fstream f;
            f.open("user_details.txt", ios::in | ios::out | ios::binary);
            do
            {
                cout << "\nAdmin Menu\n";
                cout << "\n1. Add the map of parking area\n";
                cout << "\n2. Current status of parking area\n";
                cout << "\n3. User information\n";
                cout << "\n4. Exit\n";
                cout << "\nEnter your choice: ";
                cin >> choice;
                switch (choice)
                {
                case 1:
                    p.get_slots_info();
                    p.get_parking_details();
                    break;
                case 2:
                    empty_slots = p.get_parking_status();
                    cout << "\nNumber of empty slots: " << empty_slots;
                    cout << "\nNumber of occupied slots: " << p.no_parking_slots - empty_slots;
                    break;
                case 3:
                    f.seekg(0);

                    while (f.read((char *)&p_a, sizeof(p_a)))
                    {
                        strcpy(u_d.name, p_a.name);
                        u_d.phone_number = p_a.phone_number;
                        strcpy(u_d.vehicle_number, p_a.vehicle_number);
                        strcpy(u_d.email, p_a.email);
                        u_d.allotted_parking_slot_number = p_a.allotted_parking_slot_number;
                        u_d.entry_time = p_a.entry_time;
                        u_d.token_number_entry = p_a.token_number_entry;
                        u_d.dis_ud_admin();
                    }

                    break;
                case 4:
                    break;
                default:
                    cout << "\nInvalid choice\n";
                }

            } while (choice != 4);
            f.close();
        }

        else
        {
            cout << "\nAccess denied";
        }
    }
};
admin a;
int main()
{
    int choice;
    do
    {
        cout << "\nMain Menu\n";
        cout << "\n1. User\n";
        cout << "\n2. Admin\n";
        cout << "\n3. Exit\n";
        cout << "\nEnter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            u.user_menu();
            break;
        case 2:
            a.admin_menu();
            break;
        case 3:
            break;
        default:
            cout << "\nInvalid choice\n";
        }
    } while(choice!=3);
}
