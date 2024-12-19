#include <iostream>
#include <string>

int numOf(std::string text, char character);


struct node 
{
    std::string title;
    int current = 0;
    int max = 100;
    int percentage = (current/max)*100;
    bool completion = false;
    char character;
    node* next = nullptr;
    node(std::string Title, int Current, int Max, char Character): title(Title), current(Current), max(Max), character(Character), next(nullptr){};
};


class SeasonGoals
{
    private:

    node* head = nullptr;
    
    public:

    void insertGoal(std::string title, int current, int max, char character)
    {
        node* temp = head;
        node* newNode = new node(title, current, max, character);

        if (temp == nullptr)
        {
            head = newNode;
            return;
        }
        
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }


    void display()
    {
    node* temp = head;

    while (temp != nullptr)
    {
        std::cout << temp->title << std::endl;
        std::cout << temp->current << std::endl;
        std::cout << temp->max << std::endl;

        if (temp->completion)
        {
            std::cout << "Completed" << std::endl;
        }
        else
        {
            std::cout << temp->percentage << std::endl;
        }

        temp = temp->next; // Move to the next node
    }
}



    void deleteAll()
    {
        node* temp = head;
        node* deleteThis = nullptr;

        if (head == nullptr)
        {
            deleteThis = temp;
            temp = temp->next;
            delete deleteThis;
        }

        while (temp->next != nullptr)
        {
            deleteThis = temp;
            temp = temp->next;
            delete deleteThis;
        }
        
    }


    void progressCheck(std::string text)
{
    node* temp = head;

    if (head == nullptr)
    {
        std::cout << "List empty" << std::endl;
        return;
    }

    while (temp != nullptr)
    {
        temp->current += numOf(text, temp->character); // Update the current progress

        // Safely calculate percentage as a float for accuracy
        temp->percentage = (static_cast<float>(temp->current) / temp->max) * 100;

        // Check if the task is completed
        if (temp->percentage >= 100)
        {
            temp->completion = true;
        }

        temp = temp->next; // Move to the next node
    }
}
};



int numOf(std::string text, char character)
{
    int num = 0;
    for (int i = 0; i <= text.length() + 1; i++)
    {
        if (text[i] == character)
        {
            num++;
        }
    }
    return num;
}


int main()
{
  std::string title, text;
  int current;
  int max;
  int pass, password = 1;
  char character;
  bool status = true;
  bool devMode = false;
  std::string selection;
  SeasonGoals goals;

  std::cout << "Enter pass: ";
  std::cin >> pass;
  if (pass == password)
  {
    devMode = true;
    std::cout << "DevMode activated, pay yor taxes."<<std::endl;
  }
  
  while(status ==true && devMode ==true)
  {
    std::cout<< "What is your selection?";
    std::cin>>selection;
    if(selection == "1")
    {
        std::cin.ignore(); // Clear input buffer
        std::cout<< "Enter Title: ";
        std::getline(std::cin, title);
        std::cout<<"Enter current:";
        std::cin>>current;
        std::cout<<"Enter max:";
        std::cin>>max;
        std::cout<<"Enter character: ";
        std::cin >> character;
        goals.insertGoal(title, current, max, character);
    }

    if (selection == "2")
    {
        goals.display();
        std::cout<<std::endl;
    }

    if (selection == "3")
    {
        goals.deleteAll();
    }

    if (selection == "4")
    {
        devMode = false;
    }
  }

  while (status == true && devMode == false)
  {
    std::cout<<"Begin typing: ";
    std::cin.ignore();
    std::getline(std::cin, text);
    goals.progressCheck(text);
    goals.display();

  }

}
