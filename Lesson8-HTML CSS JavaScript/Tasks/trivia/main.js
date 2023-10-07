tried_multiple_choices = false;
tried_free_answer = false;

function check_multiple_choices(selectedButton)
{
    if (!tried_multiple_choices)
    {
        var answer = selectedButton.innerHTML;
        if (answer == "Ice hockey")
        {
            const questionNode = document.getElementById("multi-question");
            const newNode = document.createElement("p");
            newNode.textContent = "Correct";

            questionNode.appendChild(newNode);

            selectedButton.style.background = "green";
            tried_multiple_choices = true;
        }
        else
        {
            const questionNode = document.getElementById("multi-question");
            const newNode = document.createElement("p");
            newNode.textContent = "Incorrect";

            questionNode.appendChild(newNode);

            selectedButton.style.background = "red";
            tried_multiple_choices = true;
        }
    }
}

function check_open_answer()
{
    var answerNode = document.getElementById("open_answer");
    var answerValue = answerNode.value;

    if (!tried_free_answer)
    {
        if (answerValue.toLowerCase() == "doctor")
        {
            const newNode = document.createElement("p");
            newNode.textContent = "Correct";

            const questionNode = document.getElementById("free-question");
            questionNode.append(newNode);

            answerNode.style.background = "green";
            tried_free_answer = true;
        }
        else
        {
            const newNode = document.createElement("p");
            newNode.textContent = "Incorrect";

            const questionNode = document.getElementById("free-question");
            questionNode.append(newNode);

            answerNode.style.background = "red";
            tried_free_answer = true;
        }
    }
}