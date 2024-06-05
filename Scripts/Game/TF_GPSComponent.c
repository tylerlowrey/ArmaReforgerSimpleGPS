[EntityEditorProps(category: "GameScripted/Gadgets", description: "GPS gadget", color: "0 0 255 255")]
class TF_GPSComponentClass : SCR_GadgetComponentClass
{
}

class TF_GPSComponent : SCR_GadgetComponent
{
	[Attribute(defvalue: "{61832C0CA964B2B9}UI/layouts/HUD/GPSDisplay.layout")]
	protected ResourceName gpsHudLayout;
	
	protected ref Widget gpsHudDisplay;
	
	protected bool shouldUpdateDisplayedCoordinates = false;
	
	protected ref RandomGenerator randomGenerator = new RandomGenerator();
	
	override bool CanBeHeld() 
	{
		return true;
	}
	
	override bool CanBeRaised() 
	{
		return true;
	}
	
	override void UpdateVisibility(EGadgetMode mode) 
	{
		super.UpdateVisibility(mode);
		
		if (mode == EGadgetMode.IN_HAND) 
		{
			if (gpsHudDisplay)
				delete gpsHudDisplay;
			
			gpsHudDisplay = GetGame().GetWorkspace().CreateWidgets(gpsHudLayout);
			ActivateGadgetUpdate();
		}
		else 
		{
			if (gpsHudDisplay)
				delete gpsHudDisplay;
			
			DeactivateGadgetUpdate();
		}
		
		Print("EGadgetMode for Handheld GPS is: " + mode);
	}
	
	override void ActivateGadgetUpdate()
	{
		super.ActivateGadgetUpdate();
		
		InventoryItemComponent itemComponent = InventoryItemComponent.Cast(GetOwner().FindComponent(InventoryItemComponent));
		if (itemComponent)
			itemComponent.ActivateOwner(true);
	}
	

	override void DeactivateGadgetUpdate()
	{
		super.DeactivateGadgetUpdate();
		
		InventoryItemComponent itemComponent = InventoryItemComponent.Cast(GetOwner().FindComponent(InventoryItemComponent));
		if (itemComponent)
			itemComponent.ActivateOwner(false);
	}
	
	override void Update(float timeSlice)
	{
		if (gpsHudDisplay)
		{
			TextWidget textWidget = TextWidget.Cast(gpsHudDisplay.FindAnyWidget("Coords"));
			GenericEntity gpsHandheldEntity = GetOwner();
			textWidget.SetText(GetGridCoordinatesAsText(gpsHandheldEntity));
		}
	}
	
	string GetGridCoordinatesAsText(IEntity entity)
	{
		vector worldPos = entity.GetOrigin();
        
        float gridSize = 100;

        int x = Math.Floor(worldPos[0] / gridSize);
        int y = Math.Floor(worldPos[2] / gridSize);
		string xString = PadIntToHundreds(x);
		string yString = PadIntToHundreds(y);
				
        string gridCoordinates = string.Format("%1-%2", xString, yString);
        
        return gridCoordinates;
	}
	
	string PadIntToHundreds(int number)
	{
		if (number < 10)
			return "00" + number.ToString();
		else if (number < 100)
			return "0" + number.ToString();
		else
			return number.ToString();
	}
	
}