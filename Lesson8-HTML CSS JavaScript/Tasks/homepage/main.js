function spin_image(image)
{
    // Checks if image if already spinning
    if (!image.classList.contains("spinning"))
    {
        // If not, adds spinning effect for 1.5 seconds
        image.classList.add("spinning");
        image.style.animation = 'spin 1.5s linear';

        // Waits until its done and removes it so you can spin it again
        image.addEventListener("animationend", function(){
            image.classList.remove("spinning");
            image.style.animation = "";
        });
    }
}