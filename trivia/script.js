// Colors.
let light_green = "#4CAF50", light_red = "#F44336";

// Changes the alternatives buttons class to disabled.
function disable_options() {
    // Gets a list with every button element inside the div with class "row".
    let buttons = document.getElementsByClassName("row")[0].childNodes;

    // Iterates over that list.
    for (let button of buttons) {
        // Gets only the button elements (because there are text elements inside it as well).
        if (button.tagName =="BUTTON") {
            // Changes the class of that button.
            button.classList.add("disabled");
        }
    }
}

// After DOM has been loaded.
document.addEventListener("DOMContentLoaded", function() {

    // Gets both "feedback" elements, one for each question.
    let fb_1 = document.getElementById("feedback_1");
    let fb_2 = document.getElementById("feedback_2");

    // Gets the first and only element with the name "correct".
    let correct = document.getElementsByName("correct")[0];

    // When the user presses the correct alternative.
    correct.addEventListener("click", function() {
        // Disable all options.
        disable_options();

        // Enable the correct option.
        correct.classList.remove("disabled");

        // Changes the class to "correct", that will give it a green background, white letters, disable hover.
        correct.classList.add("correct");

        // The first feedback element will have "correct" as text in green.
        fb_1.innerHTML = "Correct :)";
        fb_1.style.color = light_green;
    });

    // Gets a list with every element named "incorrect".
    let incorrect_list = document.getElementsByName("incorrect");

    // Iterates over that list.
    for (let incorrect of incorrect_list) {
        // When the user presses any incorrect alternative.
        incorrect.addEventListener("click", function() {
            // Disable all options.
            disable_options();

            // Enable the incorrect option pressed.
            incorrect.classList.remove("disabled");

            // Changes the class to "incorrect", that will give it a red background, white letters, disable hover.
            incorrect.classList.add("incorrect");

            // The first feedback element will have "incorrect" as text in red.
            fb_1.innerHTML = "Incorrect :(";
            fb_1.style.color = light_red;
        });
    };

    // Gets the first and only element with the name "submit_btn".
    let submit = document.getElementsByName("submit_btn")[0];

    // When the user presses the "check answer" button.
    submit.addEventListener("click", function () {
        // Gets the first and only element with the name "answer".
        let answer = document.getElementsByName("answer")[0];

        // If the answer typed is correct.
        if (answer.value.toLowerCase() == "switzerland") {
            // Changes the class to "correct", that will give it a green background, white letters, disable hover.
            submit.classList.add("correct");

            // The second feedback element will have "correct" as text in green.
            fb_2.innerHTML = "Correct :)";
            fb_2.style.color = light_green;
        }

        // If it isn't.
        else {
            // Changes the class to "incorrect", that will give it a red background, white letters, disable hover.
            submit.classList.add("incorrect");

            // The second feedback element will have "incorrect" as text in red.
            fb_2.innerHTML = "Incorrect :(";
            fb_2.style.color = light_red;
        }

        // Changes the class of the text input, where you type the answer to "disabled".
        answer.classList.add("disabled");

    });
});