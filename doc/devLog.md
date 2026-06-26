# 开发日志
## 2026-5-17  

我想开始开发我的第一款游戏了。我想开发的这款游戏叫Don’t let me go。我计划用C++制作，配合ue，编辑器采用vscode，使用github记录我的项目。我目前的大体想法是，类《大多数》风格，荒野求生类型，背景是我在学习生活中沉沦，幻想过上不平凡的生活，一次做梦，我在前往海外留学的过程中流落到一个荒岛，开始我的荒野求生，我的心情是复杂的，在崩溃之后，我振作起来，运用所学知识搭建避难所和解决饮食问题，但是因为相关知识技能有限，遇到很多挫折，直接把我干碎了，好在此时梦醒了。我庆幸只是个梦，但是第二天还是补充了相关知识，结果第二天做梦再次来到同一个荒岛，开始未竟的事业......如此循环往复，在现实和荒岛中切换，让我不断进步。这样一个背景。

今天搞定了github，其实这是我第一次真正意义上搞懂github是如何使用的，也感受到了其中的魅力，今后一定要多使用github。

## 2026-6-1

有点不像是人了，半个月转瞬即逝，赶紧开始流程啦。

今天计划制作好第一版策划案，把骨架规划好。
搞定了。尽快要实现第一版策划案的内容。

开始按照第一版策划案进入开发。默认第三人称模板已经可以运行。

>  codex实现：
> 新增第一版原型的第一个基础系统：资源拾取与简单背包。
> 当前实现内容：
>
> - 新增资源类型：树枝、石头、草、浆果、淡水
> - 新增可拾取资源 Actor
> - 角色可以按 E 与附近资源交互
> - 拾取后资源进入角色的简单背包数据
> - 屏幕会显示拾取提示和当前数量

## 2026-6-2

昨天codex实现了资源拾取和简单背包，但是我并没掌握相关方法，今天计划自己实现背包系统。

按TAB键可以显示和关闭一个空白UI了，也解决了vscode修改代码后更新到ue5的问题（ue5中Ctrl+Alt+F11进行live coding）
但是我现在还是没掌握实际应用，只是跟着GPT做了一遍。现在学习相关流程和原理，我要掌握真正的操作。

刚刚自己手搓完成了以下任务，目前看来对于如何用绑定增强按键输入和显示ui，已经没什么问题了。

> 1. UE5中创建UI
>     content->UI->user interface->widget blueprint->创建好ui显示效果
> 2. UE5中创建ToggleInventoryAction
>     content->Input->action->input action->创建ToggleInventoryAction
>     IMC_default里绑定ToggleInventory到tab键
> 3. 在build.cs中添加UMG
> 4. 在Charactor.h中添加UI类引用、Input引用
> ```protected:
> 	void ToggleInventory();
> 
> 	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = UI, Meta = (AllowPrivateAccess = "true"))
> 	TSubclassOf<UUserWidget> InventoryWidgetClass;
> 
> 	UPROPERTY()
> 	UUserWidget* InventoryWidget;
> 
> 	bool bInventoryOpen = false; 
>     ToggleInventory Input Action
> 	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category = Input, meta = (AllowPrivateAccess = "true"))
> 	class UInputAction* ToggleInventoryAction; 
> ```
> 5. 在Charactor.cpp中实现ToggleInventory和绑定Input输入
>     
> ``` void ADontLetMeGoCharacter::ToggleInventory(){
> 	if(!InventoryWidget){
> 		if(!InventoryWidgetClass){
> 			UE_LOG(LogTemp,Warning,TEXT("InventoryWidgetClass is not set!"));
> 			return ;
> 		}
> 		InventoryWidget = CreateWidget<UUserWidget>(
> 			GetWorld(),
> 			InventoryWidgetClass
> 		);
> 		if(!InventoryWidget){
> 			UE_LOG(LogTemp,Warning,TEXT("Failed to create InventoryWidget!"));
> 			return ;
> 		}
> 	}
> 
> 	if(!bInventoryOpen){
> 		InventoryWidget->AddToViewport();
> 		bInventoryOpen = true;
> 	}
> 	else{
> 		InventoryWidget->RemoveFromParent();
> 		bInventoryOpen = false;
> 	}
> }
> ```
> ```
>     //ToggleInventory
> 		EnhancedInputComponent->BindAction(ToggleInventoryAction,ETriggerEvent::Started, this, & ADontLetMeGoCharacter::ToggleInventory);
> 
> ```


下一步就是实现资源拾取和背包交互。

## 2026-6-3

今天要实现简单的资源拾取和背包交互，完成简单的背包ui。

今天完成了资源拾取和背包交互的前置条件，现在是能按e检测到目标actor并且输出actor的itemName了，还是有些进步和进展的。今日收获总结如下：
> 1. 复习增强输入设置，这次是按E键。
> 2. Line Trace，获取碰撞物品信息：
>   ```FVector start = FollowCamera->GetComponentLocation();
>       FVector end = start + FollowCamera->GetForwardVector()*500.f;
>   FHitResult Hit;
>    bool bHit= GetWorld()->LineTraceSingleByChannel(
>       Hit,
>        start,
>        end,
>        ECC_Visibility
>    )
>   if(bHit){
>        AActor* HitActor=Hit.GetActor();
>        APickupItem* Item=Cast<APickupItem>(HitActor);
>        if(Item){
>            UE_LOG(
>                LogTemp,
>                Warning,
>                TEXT("Item Name %s"),
>                *Item->ItemName
>            );
>        }
>    }
>

本来今天就要实现资源拾取和背包交互的。但是确实遇见很多小麻烦，把蓝图Actor换成C++类Actor，这样才能用cast获取actor信息。

明天一定要完成这项小功能，而且还有明天原本的任务安排。

## 2026-6-4
今天要完成昨天剩下的任务以及实现视角设置。

终于实现了简单的资源拾取和背包交互。

今天掌握的功能有
>1. 把物品信息打印到屏幕上：
>```
>    if(GEgine){
>        FString msg=FString::FPrint(
>            TEXT("Pick up:%s"),
>            *Item->ItemName
>        );
>        GEngine->AddOnScreenDebugMessage(
>            -1,
>            3.f,
>            FColor::Green,
>            msg
>        );
>    }
>```
>2. 拾取物品的逻辑：检测物品，记录物品，销毁物品
>```
>Inventory.Add(Item->ItemName);
>
>Item->destroy();
>```
>背包数据更新：
>背包ui的widget全部继承于C++类，分别创建一个背包ui和一个背包内容text的类。
>4. 背包内容text类中实现：
>```
>    UPROPERTY(Meta=(BindWidget))
>    UTextBlock* ItemNameText;
>
>    void SetItemName(const FString& Name){
>        if(ItemNameText){
>            ItemNameText->SetText(FString::Fromstring(Name));
>        }
>    }
>```
>5. 背包本身ui类中实现：
>```Class UScrollBox;
>    Class UItemEntryWidget;
>
>    UPROPERTY(Meta= (BindWidget))
>    UScrollBox* ItemList;
>
>    UPROPERTY(EditAnywhere,BlueprintReadOnly,Category= Inventpry)
>    TSubclassOf<UItemEntryWidget> ItemEntryClass;
>
>    void RefreshInventory(const TArray<FString>& Items){
>        if(!ItemList){
>            return ;
>        }
>        ItemList->ClearChildren();
>        for(const FString& ItemName: Items){
>            UItemEntryWidget* Entry = CreateWidget<UItemEntryWidget>(GetWorld(),ItemEntryClass);
>            if(Entry){
>                Entry->SetItemName(ItemName);
>                ItemList->AddChile(Entry);
>            }
>        }
>    }
>```
>实现视角转换，舍弃了模板的视角，更换为了俯视视角。
>6. 添加独立相机
>```
>	PrimaryActorTick.bCanEverTick = true;
>	Camera=CreateDefaultSubobject<UCameraComponent>(TEXT>("Camera"));
>	RootComponent = Camera;
>```
>7. 设置相机位置和角度
>```
>TargetCharacter = UGameplayStatics::GetPlayerCharacter(this,0);
>	if(!TargetCharacter){
>		return ;
>	}
>	FVector PlayerLocation = TargetCharacter->GetActorLocation();
>	FVector CameraLocation = PlayerLocation+FVector(-600.f,0.f,>600.f);
>	SetActorLocation(CameraLocation);
>	SetActorRotation(
>		FRotator(
>			0.f,
>			0.f,
>			0.f
>		)
>	);
>```
>8. 让相机跟随角色
>```
>void AFollowCameraActor::Tick(float DeltaTime)
>{
>	Super::Tick(DeltaTime);
>	if(!TargetCharacter){
>		return ;
>	}
>	FVector TargetLocation=TargetCharacter->GetActorLocation()>+FVector(
>		-600.f,
>		0.f,
>		600.f);
>	//SetActorLocation(TargetLocation);
>	FVector NewLocation = FMath::VInterpTo(GetActorLocation(),TargetLocation,DeltaTime,5.f);
>	SetActorLocation(NewLocation);
>	FRotator LookAtRotation = (TargetCharacter->GetActorLocation()-GetActorLocation()).Rotation();
>
>	SetActorRotation(LookAtRotation);
>}
>```
>
>9. 除此之外还更新优化了资源拾取的方式，从LineTrace改为了SphereTrace>的方式。
>```
>#include "KismetSystemLibrary.h"
>
>bool bHit = UKismetSystemLibrary::SphereTraceSingle(
>		GetWorld(),
>		Start,
>		End,
>		80.f,
>		UEngineTypes::ConvertToTraceType(ECC_Visibility),
>		false,
>		{},
>		EDrawDebugTrace::ForDuration,
>		Hit,
>		true
>	);
>
>```


## 2026-6-8

玩耍的时间过得总是这么快，5号是因为准备第二天的笔试，6号是因为笔试完想放松，结果一放松就给7号也放过去了。

今天要把背包结构更新，原本只是存储string，现在要改为存数据结构。

今天完成了背包结构的更新，新创建了DataTable，资源拾取改变DataTable，背包读取数据显示。
>```
>USTRUCT(BlueprintType)
>struct FItemData:public FTableRowBase{
>    GENERATED_BODY()
>
>    UPROPERTY(EditAnywhere,BlueprintReadOnly)
>    FName ItemID;
>
>    UPROPERTY(EditAnywhere,BlueprintReadOnly)
>    FText DisplayName;
>
>    UPROPERTY(EditAnywhere,BlueprintReadOnly)
>    int32 MaxStack= 99;
>
>    UPROPERTY(EditAnywhere,BlueprintReadOnly)
>    int32 BuyPrice=0;
>
>    UPROPERTY(EditAnywhere,BlueprintReadOnly)
>    int32 SellPrice=0;
>};
>
>USTRUCT(BlueprintType)
>struct FInventorySlot{
>    GENERATED_BODY()
>
>    UPROPERTY(EditAnywhere, BlueprintReadWrite)
>    FName ItemID;
>
>    UPROPERTY(EditAnywhere, BlueprintReadWrite)
>    int32 Count=0;
>};
>```
把各部分代码都分开独立在了各自文件夹里，方便日后管理。
优化了资源拾取的检测方式。

## 2026-6-9
今天实现角色状态和状态显示
>Hunger、Thirst、Spirit、Stamina
>```
>
>	PROPERTY(EditAnywhere,BlueprintReadOnly)
>	FStatusValue Hunger;
>
>	PROPERTY(EditAnywhere,BlueprintReadOnly)
>	FStatusValue Thirst;
>
>	PROPERTY(EditAnywhere,BlueprintReadOnly)
>	FStatusValue Spirit;
>
>	PROPERTY(EditAnywhere,BlueprintReadOnly)
>	FStatusValue Stamina;
>``
>Foder:Status
>UI/StatusWidget

## 2026-6-10
今天要实现角色移动消耗体力，不移动恢复体力。
实现状态值变为0时回到房间地图。
>```
>void SetMoving(bool bMoving);
>
>	bool IsMoving()const{
>		return bIsMoving;
>	}
>
>if (StatusComponent)
>	{
>    	StatusComponent->SetMoving(
>        	!MovementVector.IsNearlyZero()
>    	);
>	}
>if (bIsMoving)
>{
>    Stamina.CurrentValue -= 8.f * DeltaTime;
>}
>else
>{
>    Stamina.CurrentValue += 5.f * DeltaTime;
>}
>
>void ADontLetMeGoCharacter::Tick(float DeltaTime)
>{
>    Super::Tick(DeltaTime);
>
>
>    if (bIsChangingLevel)
>    {
>        return;
>    }
>
>    if (StatusComponent &&
>        StatusComponent->Hunger.CurrentValue <= 0.f)
>    {
>        bIsChangingLevel = true;
>		if (StatusWidget)
>{
    StatusWidget->SetVisibility(ESlateVisibility::Hidden);
}	
        UGameplayStatics::OpenLevel(
            GetWorld(),
            FName("RoomMap")
        );
    }
}
>```

## 2026-6-11
使用GameInstance完成昨天没完成的切换关卡关闭状态widget显示。
>```
>UCLASS()
>class DONTLETMEGO_API UDontLetMeGoGameInstance : public >UGameInstance
>{
>	GENERATED_BODY()
>	
>public:
>	bool bIsWake=false;
>	void ChangeMap();
>
>};
>void UDontLetMeGoGameInstance::ChangeMap(){
>    bIsWake=true;
>
>    UWorld* World=GetWorld();
>    if(!World)return;
>
>    if(bIsWake){
>        UGameplayStatics::OpenLevel(World,FName("RoomMap"));
>
>    }else{
>        UGameplayStatics::OpenLevel(World,FName("IslandMap"));
>    }
>
>
>}
>
>	if(Hunger.CurrentValue<=0||Thirst.CurrentValue||Spirit.CurrentValue){
>		UDontLetMeGoGameInstance*GI=Cast<UDontLetMeGoGameInstance>(GetWorld()>->GetGameInstance());
>		if(GI){
>			GI->ChangeMap();
>		}
>	}
>
>
>	UDontLetMeGoGameInstance* GI=Cast<UDontLetMeGoGameInstance>>(GetGameInstance());
>	
>	if(StatusWidgetClass&&GI&&!GI->bIsWake)
>```

耐力值到0时无法移动
>```
>if (StatusComponent)
>	{	
>    	StatusComponent->SetMoving(
>        	!MovementVector.IsNearlyZero()
>    	);
>		if(StatusComponent->Stamina.CurrentValue<=0){
>			return;
>		}
>	}
>```
今天实现游戏开始菜单

## 2026-6-16

这五天因为准备考试和组会汇报，没有进展，今天考完了也汇报完了，可以继续进行。

今天目标实现游戏开始菜单。有多时间就继续实现使用物品功能和制作物品功能。

实现了游戏开始菜单，点击开始按钮跳转到roommap
>```
>void UDontLetMeGoGameInstance::Init(){
>    Super::Init();
>    FTimerHandle MenuTimer;
>    GetTimerManager().SetTimer(MenuTimer, this,&UDontLetMeGoGameInstance::ShowMenuWidget,0.2f,false);
>
>}
>
>void UDontLetMeGoGameInstance::ShowMenuWidget(){
>    if(bMenuShow){return ;}
>    FString CurrentMap = GetWorld()->GetMapName();
>    CurrentMap.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);
>    if(!CurrentMap.Contains("Menu")&&!CurrentMap.Contains("MainMenu")){
>        return;
>    }
>     if(MenuWidgetClass){
>        UUserWidget* Menu=CreateWidget<UUserWidget>>(this,MenuWidgetClass);
>        if(Menu){
>            Menu->AddToViewport();
>            
>            if(APlayerController* PC=GetWorld()->GetFirstPlayerController()){
>                PC->bShowMouseCursor = true;
>
>                FInputModeUIOnly InputMode;
>                InputMode.SetWidgetToFocus>(Menu->TakeWidget());
>                InputMode.SetLockMouseToViewportBehavior>(EMouseLockMode::DoNotLock);
>                PC->SetInputMode(InputMode);
>        
>    }
>    }   
>    }
>}
>
>void UDontLetMeGoGameInstance::StartGame(){
>    if(APlayerController* PC=GetWorld()->GetFirstPlayerController()){
>        PC->bShowMouseCursor = false;
>        FInputModeGameOnly InputMode;
>        PC->SetInputMode(InputMode);
>    }
>    bMenuShow = false;
>    UGameplayStatics::OpenLevel(GetWorld(),FName>("RoomMap"));
>}
>
>void UDontLetMeGoGameInstance::QuitGame(){
>    UKismetSystemLibrary::QuitGame(GetWorld(),nullptr,EQuitPreference::Quit,false);
>}
>
>void UMenuWidget::NativeConstruct(){
>    Super::NativeConstruct();
>
>    if(StartButton){
>        StartButton->OnClicked.AddDynamic(
>            this,
>            &UMenuWidget::OnStartClicked
>        );
>    }
>    if(QuitButton){
>        QuitButton->OnClicked.AddDynamic(
>            this,
>            &UMenuWidget::OnQuitClicked
>        );
>    }
>}
>
>void UMenuWidget::OnStartClicked(){
>    if(UDontLetMeGoGameInstance* GI = GetGameInstance<UDontLetMeGoGameInstance>()){
>        GI->StartGame();
>    }
>
>}
>
>void UMenuWidget::OnQuitClicked(){
>    if(UDontLetMeGoGameInstance* GI = GetGameInstance<UDontLetMeGoGameInstance>()){
>        GI->QuitGame();
>    }
>}
>```

## 2026-6-17
今天要完成优化开始菜单和实现入睡传送荒岛地图的功能。

开始菜单用另外的地图展示，布置了基础场景和摄影机。

实现了入睡传送到孤岛的功能


## 2026-6-20
今天通过重叠事件方式实现了显示交互信息的功能，靠近床显示“按E 入睡”。
>1. 重叠事件
>```
>	UPROPERTY(VisibleAnywhere)
>	class USphereComponent* InteractionSphere;
>BedMesh = CreateDefaultSubobject<UStaticMeshComponent>(
>		TEXT("BedMesh")
>	);
>	RootComponent = BedMesh;
>	InteractionSphere=CreateDefaultSubobject<USphereComponent>>(TEXT("InteractionSphere"));
>	InteractionSphere->SetupAttachment(BedMesh);
>	InteractionSphere->SetSphereRadius(200.f);
>	
>	InteractionSphere->OnComponentBeginOverlap.
>	AddDynamic(
>   	 this,
>   	 &ABedActor::OnBeginOverlap
>	);
>
>	InteractionSphere->OnComponentEndOverlap.
>	AddDynamic(
>    	this,
>  	  &ABedActor::OnEndOverlap
>	);
>
>
>```
>2. 显示交互信息
>```
>    UPROPERTY(VisibleAnywhere,Category= UI)
>	class UWidgetComponent* InteractPromptWidget;
>
>    InteractPromptWidget=CreateDefaultSubobject<UWidgetComponent>>(TEXT("InteractPrompt"));
>	InteractPromptWidget->SetupAttachment(RootComponent);
>	InteractPromptWidget->SetWidgetSpace(EWidgetSpace::Screen);
>	InteractPromptWidget->SetDrawSize(FVector2D(200,50));
>	InteractPromptWidget->SetVisibility(false);
>
>
>    void ABedActor::OnBeginOverlap(
>    UPrimitiveComponent* OverlappedComp,
>    AActor* OtherActor,
>    UPrimitiveComponent* OtherComp,
>    int32 OtherBodyIndex,
>    bool bFromSweep,
>    const FHitResult& SweepResult
>)
>{
>	InteractPromptWidget->SetVisibility(true);
>    if(GEngine){
>		FString BedInfo=FString::Printf(TEXT("Sleep!"));
>		GEngine->AddOnScreenDebugMessage(
>			-1,
>			2.f,
>			FColor::Yellow,
>			BedInfo	
>		);
>	}
>}
>void ABedActor::OnEndOverlap(
>    UPrimitiveComponent* OverlappedComp,
>    AActor* OtherActor,
>    UPrimitiveComponent* OtherComp,
>    int32 OtherBodyIndex
>)
>{	
>	InteractPromptWidget->SetVisibility(false);
>    if(GEngine){
>		FString BedInfo=FString::Printf(TEXT("Wake Up!"));
>		GEngine->AddOnScreenDebugMessage(
>			-1,
>			2.f,
>			FColor::Yellow,
>			BedInfo	
>		);
>	}
>}
>```

游戏开发真是没有想象中的简单，好多好多需要考虑的细节和功能实现。
现在我实现了最基本的游戏框架了，接下来就得实现各种各样的基础功能、玩法和剧情了。
现在最紧要的就是实现使用物品和制作物品的功能。后续再慢慢推进吧。
总之就是真没想象中的简单。更别提之后美术音乐的事项了。
不过一步一步来吧，总能实现的。

## 2026-6-21
今天要实现使用物品和制作物品的功能。


## 2026-6-23
结果重构背包系统重构到现在，现在背包系统比较完善了，uniformgrid实现，能触发点击事件。
接下来马上实现使用物品的功能和制造物品的功能。

今日实现：重构背包系统，优化背包ui，实现使用物品。
>```
>void UInventoryWidget::GetGridPosition(int32 SlotIndex, int32& OutRow, int32& OutColumn) const
>{
>    OutRow = SlotIndex / GridColumns;
>    OutColumn = SlotIndex % GridColumns;
>}
>
>void UInventoryWidget::HandleSlotClicked(int32 SlotIndex)
>{
>    SelectedSlot = SlotIndex;
>
>    for (int32 i = 0; i < SlotWidgets.Num(); i++)
>    {
>        if (SlotWidgets[i])
>        {
>            SlotWidgets[i]->SetSelected(
>                i == SelectedSlot
>            );
>        }
>    }
>
>    OnSlotClicked(SlotIndex);
>}
>
>void UInventoryWidget::SetInventoryComponent>(UInventoryComponent* InComponent)
>{
>    if (InventoryComponent)
>    {
>        InventoryComponent->OnItemUsed.RemoveDynamic(
>            this,
>            &UInventoryWidget::HandleInventoryChanged
>        );
>    }
>
>    InventoryComponent = InComponent;
>
>    if (InventoryComponent)
>    {
>        InventoryComponent->OnItemUsed.AddDynamic(
>            this,
>            &UInventoryWidget::HandleInventoryChanged
>        );
>
>        RefreshInventory(InventoryComponent->GetSlots());
>    }
>}
>
>void UInventoryWidget::HandleInventoryChanged(
>    int32 SlotIndex,
>    FName ItemID)
>{
>    if (InventoryComponent)
>    {
>        RefreshInventory(
>            InventoryComponent->GetSlots()
>        );
>    }
>}
>
>DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSlotClicked, >int32, SlotIndex);
>
>FReply UItemEntryWidget::NativeOnMouseButtonDown(
>    const FGeometry& InGeometry,
>    const FPointerEvent& InMouseEvent)
>{
>    if (InMouseEvent.GetEffectingButton() == >EKeys::LeftMouseButton)
>    {
>        OnSlotClicked.Broadcast(SlotIndex);
>        return FReply::Handled();
>    }
>
>    if (InMouseEvent.GetEffectingButton() == >EKeys::RightMouseButton)
>    {
>        OnSlotRightClicked.Broadcast(SlotIndex);
>        return FReply::Handled();
>    }
>
>    return Super::NativeOnMouseButtonDown(
>        InGeometry,
>        InMouseEvent);
>}
>
>```
>
>
>## 2026-6-24
>犯了一个非常非常非常严重的问题，因为uasset占存储大，上传github太>慢，于是我把所有uasset都删了，结果连本地的也删了。。。
>重新创建所有的.uasset，包括所有资产蓝图，UIwidget。
>
>今天实现了与背包的交互，左键点击背包格子显示高亮以及显示背包格子中的>物品信息。
>```
>
>UCLASS()
>class DONTLETMEGO_API UItemInfoWidget : public UUserWidget
>{
>	GENERATED_BODY()
>	
>	UPROPERTY(meta = (BindWidget))
>	class UTextBlock* ItemNameText;
>	UPROPERTY(meta = (BindWidget))
>	class UTextBlock* HungerValue;
>	UPROPERTY(meta = (BindWidget))
>	class UTextBlock* ThirstValue;
>	UPROPERTY(meta = (BindWidget))
>	class UTextBlock* SpiritValue;
>	UPROPERTY(meta = (BindWidget))
>	class UTextBlock* StaminaValue;
>
>public:
>	UFUNCTION(BlueprintCallable)
>	void SetItemInfo(
>    const FItemData& Data
>	);
>};
>
>// Fill out your copyright notice in the Description page of >Project Settings.
>
>
>#include "ItemInfoWidget.h"
>#include "Components/TextBlock.h"
>
>void UItemInfoWidget::SetItemInfo(
>    const FItemData& Data)
>{
>    ItemNameText->SetText(
>        Data.DisplayName
>    );
>    if (Data.RecoverHunger >=0)
>    {
>        FString HungerStr = FString::Printf(TEXT("+%.0f"), Data.>RecoverHunger);
>        HungerValue->SetText(FText::FromString(HungerStr));
>    }else if(Data.RecoverHunger < 0){
>        FString HungerStr = FString::Printf(TEXT("-%.0f"), Data.>RecoverHunger);
>        HungerValue->SetText(FText::FromString(HungerStr));
>    }
>
>    if (Data.RecoverSpirit >=0)
>    {
>        FString SpiritStr = FString::Printf(TEXT("+%.0f"), Data.>RecoverSpirit);
>        SpiritValue->SetText(FText::FromString(SpiritStr));
>    }else if(Data.RecoverSpirit < 0){
>        FString SpiritStr = FString::Printf(TEXT("-%.0f"), Data.>RecoverSpirit);
>        SpiritValue->SetText(FText::FromString(SpiritStr));
>    }
>
>    if (Data.RecoverStamina >=0)
>    {
>        FString StaminaStr = FString::Printf(TEXT("+%.0f"), >Data.RecoverStamina);
>        StaminaValue->SetText(FText::FromString(StaminaStr));
>    }else if(Data.RecoverStamina < 0){
>        FString StaminaStr = FString::Printf(TEXT("-%.0f"), >Data.RecoverStamina);
>        StaminaValue->SetText(FText::FromString(StaminaStr));
>    }
>
>    if (Data.RecoverThirst>=0)
>    {
>        FString ThirstValueStr = FString::Printf(TEXT("+%.0f"), >Data.RecoverThirst);
>        ThirstValue->SetText(FText::FromString(ThirstValueStr));
>    }else if(Data.RecoverThirst< 0){
>        FString ThirstValueStr = FString::Printf(TEXT("-%.0f"), >Data.RecoverThirst);
>        ThirstValue->SetText(FText::FromString(ThirstValueStr));
>    }
>
>    
>}
>
>if (ItemInfoWidget)
>    {
>    ItemInfoWidget->RemoveFromParent();
>    ItemInfoWidget = nullptr;
>
>    }
>    SelectedSlot = SlotIndex;
>
>    for (int32 i = 0; i < SlotWidgets.Num(); i++)
>    {
>        if (SlotWidgets[i])
>        {
>            SlotWidgets[i]->SetSelected(
>                i == SelectedSlot
>            );
>        }
>    }
>    
>    OnSlotClicked(SlotIndex);
>    
>    if(!InventoryComponent)
>    {
>        return;
>    }
>
>    const TArray<FInventorySlot>& InfoSlots =
>        InventoryComponent->GetSlots();
>
>    if(!InfoSlots.IsValidIndex(SlotIndex))
>    {
>        return;
>    }
>
>    const FInventorySlot& InfoSlot = InfoSlots[SlotIndex];
>    if(InfoSlot.ItemID.IsNone()||InfoSlot.Count<1){
>        
>        return;
>    }
>    
>
>    if(ItemInfoWidgetClass)
>    {
>        ItemInfoWidget =
>            CreateWidget<UItemInfoWidget>(
>                this,
>                ItemInfoWidgetClass
>            );
>
>    }
>    const FItemData* InfoData =
>        InventoryComponent->GetItemData(
>            InfoSlot.ItemID
>        );
>
>    if(InfoData && ItemInfoWidget)
>    {
>        ItemInfoWidget->SetItemInfo(
>            *InfoData
>        );
>        FVector2D MousePos;
>
>            GetOwningPlayer()->GetMousePosition(
>                MousePos.X,
>                MousePos.Y
>            );
>            ItemInfoWidget->SetPositionInViewport(
>            MousePos
>            );    
>            ItemInfoWidget->SetVisibility(
>                ESlateVisibility::HitTestInvisible
>            );
>            ItemInfoWidget->AddToViewport();
>        
>      
>    }
>    
>    void UInventoryWidget::CloseItemInfo(){
>    if(ItemInfoWidget)
>    {
>        ItemInfoWidget->RemoveFromParent();
>        ItemInfoWidget = nullptr;
>    }
>}
>
>//character.cpp:
>    UInventoryWidget* InvWidget = Cast<UInventoryWidget>>(InventoryWidget);
>		if(InvWidget){
>			InvWidget->CloseItemInfo();
>		}
>```
>
>## 2026-6-25
>今天解决了很多问题。
>首先是livingcode同步问题，cscode一定是要用developmentEditor >build，之前用的不是Editor，导致每次打开都不同步。
>
>实现了右键弹出使用和丢弃的按钮窗口，点击使用能够使用可使用物品，点击>丢弃会丢弃物品。
>
>>1. 新建useWidgetClass文件
>> 在ItemUseInfoWidget.h中：
>>```
>>UCLASS()
>>class DONTLETMEGO_API UItemUseInfoWidget : public >UUserWidget
>>{
>>	GENERATED_BODY()
>>	
>>	UPROPERTY(meta=(BindWidget))
>>	class UButton* UseButton;
>>
>>	UPROPERTY(meta = (BindWidget))
>>	class UButton* DropButton;
>>
>> 	
>>public:
>>
>>	void NativeConstruct() override;
>>
>>	UFUNCTION()
>>	void HandleUseClicked();
>>
>>	UFUNCTION()
>>	void HandleDropClicked();
>>
>>	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUseClicked);
>>	DECLARE_DYNAMIC_MULTICAST_DELEGATE>(FOnDropClicked);
>>	
>>	UPROPERTY(BlueprintAssignable)
>>	FOnUseClicked OnUseClicked;
>>	
>>	UPROPERTY(BlueprintAssignable)
>>	FOnDropClicked OnDropClicked;
>>};
>>
>> 
>>```
>>.cpp中
>>```
>>    
>>void UItemUseInfoWidget::NativeConstruct(){
>>    Super::NativeConstruct();
>>
>>    if(UseButton){
>>        UseButton->OnClicked.AddDynamic(
>>            this,
>>            &UItemUseInfoWidget::HandleUseClicked
>>        );
>>    }
>>    if(DropButton){
>>        DropButton->OnClicked.AddDynamic(
>>            this,
>>            &UItemUseInfoWidget::HandleDropClicked
>>        );
>>    }
>>}
>>
>>void UItemUseInfoWidget::HandleUseClicked()
>>{
>>    OnUseClicked.Broadcast();
>>}
>>
>>void UItemUseInfoWidget::HandleDropClicked()
>>{
>>    OnDropClicked.Broadcast();
>>}
>>
>>```
>>2. 在InvnetoryWidgt.cpp中实现按钮弹窗和点击实现功能
>>
>>```
>>
>>void UInventoryWidget::HandleSlotRightClicked(int32 >SlotIndex)
>>{
>>    CloseItemInfo();
>>    CloseItemUseInfo();
>>    SelectedSlot = SlotIndex;
>>     SelectedDropSlot = SlotIndex;
>>     
>>    for (int32 i = 0; i < SlotWidgets.Num(); i++)
>>    {
>>        if (SlotWidgets[i])
>>        {
>>            SlotWidgets[i]->SetSelected(
>>                i == SelectedSlot
>>            );
>>        }
>>    }
>>    if(!InventoryComponent)
>>    {
>>        return;
>>    }
>>
>>    const TArray<FInventorySlot>& InfoSlots =
>>        InventoryComponent->GetSlots();
>>
>>    if(!InfoSlots.IsValidIndex(SlotIndex))
>>    {
>>        return;
>>    }
>>
>>    const FInventorySlot& InfoSlot = InfoSlots>[SlotIndex];
>>    if(InfoSlot.ItemID.IsNone()||InfoSlot.Count<1){
>>        
>>        return;
>>    }
>>    
>>
>>    if(ItemUseInfoWidgetClass)
>>    {
>>        ItemUseInfoWidget =
>>            CreateWidget<UItemUseInfoWidget>(
>>                this,
>>                ItemUseInfoWidgetClass
>>            );
>>
>>    }
>>    ItemUseInfoWidget->OnUseClicked.AddDynamic(
>>    this,
>>    &UInventoryWidget::OnUseClicked
>>    );
>>    
>>    ItemUseInfoWidget->OnDropClicked.AddDynamic(
>>        this,
>>        &UInventoryWidget::OnDropClicked
>>    );
>>
>>    const FItemData* InfoData =
>>        InventoryComponent->GetItemData(
>>            InfoSlot.ItemID
>>        );
>>
>>    if(InfoData && ItemUseInfoWidget)
>>    {
>>        
>>        FVector2D MousePos;
>>
>>            GetOwningPlayer()->GetMousePosition(
>>                MousePos.X,
>>                MousePos.Y
>>            );
>>            ItemUseInfoWidget->SetPositionInViewport(
>>            MousePos
>>            );    
>>            ItemUseInfoWidget->SetVisibility(
>>                ESlateVisibility::Visible
>>            );
>>            ItemUseInfoWidget->AddToViewport();
>>        
>>      
>>    }
>>    OnSlotRightClicked(SlotIndex);
>>}
>>
>>void UInventoryWidget::OnUseClicked()
>>{
>>    if(!InventoryComponent)
>>    {
>>        return;
>>    }
>>
>>    InventoryComponent->UseItemAt(
>>       SelectedUseSlot
>>    );
>>
>>    CloseItemUseInfo();
>>}
>>void UInventoryWidget::OnDropClicked()
>>{
>>    if(!InventoryComponent)
>>    {
>>        return;
>>    }
>>
>>    InventoryComponent->RemoveItemAt(
>>       SelectedDropSlot
>>    );
>>
>>    CloseItemUseInfo();
>>}
>>```
>
>但是还只是相当简陋的模式，比如丢弃还没实现在地图中返还相应物品。但是>作为原型功能应该够了。
>
>明天开始要实现物品制作的功能。
>
>
>## 2026-6-26
>
>结果还是没有开始物品制作环境，因为想着把现有功能先完善了。
>
>今天实现：
>1. 背包格子始终按顺序填充，用完变空了后续也能填上。
>``` 
>
>//InventoryComponent.cpp中：
>bool UInventoryComponent::AddItem(FName ItemID, int32 Count)
>{
>    if (Count <= 0)
>    {
>        return false;
>    }
>
>    const FItemData* Data = GetItemData(ItemID);
>    if (!Data)
>    {
>        return false;
>    }
>
>    int32 MaxStack = Data->MaxStack;
>
>    // 1. 先堆叠到已有同 ID 的格子
>    for (FInventorySlot& Slot : Slots)
>    {
>        if (Slot.ItemID != ItemID)
>        {
>            continue;
>        }
>
>        if (Slot.Count >= MaxStack)
>        {
>            continue;
>        }
>
>        int32 SpaceLeft = MaxStack - Slot.Count;
>
>        if (Count <= SpaceLeft)
>        {
>            Slot.Count += Count;
>            OnItemUsed.Broadcast(-1, ItemID);
>            return true;
>        }
>
>        Slot.Count = MaxStack;
>        Count -= SpaceLeft;
>    }
>
>    // 2. 再填充空槽位（ItemID == NAME_None 或 Count <= 0）
>    for (FInventorySlot& Slot : Slots)
>    {
>        if (!Slot.ItemID.IsNone() && Slot.Count > 0)
>        {
>            continue;
>        }
>
>        int32 AddCount = FMath::Min(Count, MaxStack);
>        Slot.ItemID = ItemID;
>        Slot.Count = AddCount;
>        Count -= AddCount;
>
>        if (Count <= 0)
>        {
>            OnItemUsed.Broadcast(-1, ItemID);
>            return true;
>        }
>    }
>
>    // 3. 还有剩余，新增格子
>    while (Count > 0)
>    {
>        FInventorySlot NewSlot;
>        NewSlot.ItemID = ItemID;
>        NewSlot.Count = FMath::Min(Count, MaxStack);
>        Count -= NewSlot.Count;
>        Slots.Add(NewSlot);
>    }
>
>    OnItemUsed.Broadcast(-1, ItemID);
>    return true;
>}
>```
>2. 格子的选择统一。
>```//InventoryWidget.h：
>
>	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
>	int32 SelectedSlot = -1;
>```
>3. 靠近资源物品显示交互信息。
>```//PickupItem.h:
>    UPROPERTY(VisibleAnywhere)
>    class USphereComponent* InteractionSphere;
>
>    UPROPERTY(VisibleAnywhere, Category = "UI")
>    class UWidgetComponent* InteractPromptWidget;
>    UFUNCTION()
>    void OnBeginOverlap(
>        UPrimitiveComponent* OverlappedComp,
>        AActor* OtherActor,
>        UPrimitiveComponent* OtherComp,
>        int32 OtherBodyIndex,
>        bool bFromSweep,
>        const FHitResult& SweepResult
>    );
>
>    UFUNCTION()
>    void OnEndOverlap(
>        UPrimitiveComponent* OverlappedComp,
>        AActor* OtherActor,
>        UPrimitiveComponent* OtherComp,
>        int32 OtherBodyIndex
>    );
>
>    //PickupItem.cpp:
>     PickupItemMesh = >CreateDefaultSubobject<UStaticMeshComponent>(TEXT>("PickupItemMesh"));
>    RootComponent = PickupItemMesh;
>
>    InteractionSphere = CreateDefaultSubobject<USphereComponent>>(TEXT("InteractionSphere"));
>    InteractionSphere->SetupAttachment(PickupItemMesh);
>    InteractionSphere->SetSphereRadius(75.f);
>
>    InteractPromptWidget = >CreateDefaultSubobject<UWidgetComponent>(TEXT>("InteractPrompt"));
>    InteractPromptWidget->SetupAttachment(PickupItemMesh);
>    InteractPromptWidget->SetWidgetSpace(EWidgetSpace::Screen);
>    InteractPromptWidget->SetVisibility(false);
>
>    InteractionSphere->OnComponentBeginOverlap.AddDynamic>(this, &APickupItem::OnBeginOverlap);
>    InteractionSphere->OnComponentEndOverlap.AddDynamic(this, &>APickupItem::OnEndOverlap);
>
>
>    void APickupItem::OnBeginOverlap(
>    UPrimitiveComponent* OverlappedComp,
>    AActor* OtherActor,
>    UPrimitiveComponent* OtherComp,
>    int32 OtherBodyIndex,
>    bool bFromSweep,
>    const FHitResult& SweepResult
>)
>{
>    if (bIsActive && InteractPromptWidget)
>    {
>        InteractPromptWidget->SetVisibility(true);
>    }
>
>    if (GEngine)
>    {
>        GEngine->AddOnScreenDebugMessage(-1, 2.0f, >FColor::Yellow, TEXT("Item!"));
>    }
>}
>
>void APickupItem::OnEndOverlap(
>    UPrimitiveComponent* OverlappedComp,
>    AActor* OtherActor,
>    UPrimitiveComponent* OtherComp,
>    int32 OtherBodyIndex
>)
>{
>    if (InteractPromptWidget)
>    {
>        InteractPromptWidget->SetVisibility(false);
>    }
>}
>```
>4. 资源物品可刷新。
>```//PickupItem.h
>   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = >"Item")
>    bool bRespawnable = true;
>
>    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = >"Item")
>    float RespawnTime = 5.0f;
>
>    UPROPERTY(BlueprintReadOnly, Category = "Item")
>    bool bIsActive = true;
>    private:
>    FTimerHandle RespawnTimerHandle;
>    //PickupItem.cpp:
>    
>void APickupItem::SetActive(bool bActive)
>{
>    bIsActive = bActive;
>    SetActorHiddenInGame(!bActive);
>    SetActorEnableCollision(bActive);
>
>    if (InteractPromptWidget)
>    {
>        InteractPromptWidget->SetVisibility(false);
>    }
>}
>
>void APickupItem::OnPickedUp()
>{
>    if (!bIsActive) return;
>
>    if (!bRespawnable)
>    {
>        Destroy();
>        return;
>    }
>
>    SetActive(false);
>
>    if (bRespawnable && RespawnTime > 0.0f)
>    {
>        GetWorld()->GetTimerManager().SetTimer(
>            RespawnTimerHandle,
>            this,
>            &APickupItem::Respawn,
>            RespawnTime,
>            false
>        );
>    }
>}
>
>void APickupItem::Respawn()
>{
>    SetActive(true);
>}
>
>//Character.cpp:
>Item->OnPickedUp();
>```
>5. 丢弃物品会原地返还相应物品。
>```
>//InventoryType.h:
>    UPROPERTY(EditAnywhere, BlueprintReadOnly)
>    TSubclassOf<AActor> PickupActorClass = nullptr;
>//InventoryComponent.h:
>    
>    UPROPERTY(EditDefaultsOnly, Category="Inventory")
>    float DropDistance = 100.0f;                
>
>    UPROPERTY(EditDefaultsOnly, Category="Inventory")
>    float DropHeight = 50.0f;                   
>
>    UFUNCTION(BlueprintCallable)
>    bool DropItemAt(int32 SlotIndex);            
>
>//InventoryComponent.cpp:
>    
>bool UInventoryComponent::DropItemAt(int32 SlotIndex)
>{
>    if (!Slots.IsValidIndex(SlotIndex))
>    {
>        return false;
>    }
>
>    FInventorySlot& DropSlot = Slots[SlotIndex];
>    if (DropSlot.ItemID.IsNone() || DropSlot.Count <= 0)
>    {
>        return false;
>    }
>
>    FName DroppedItemID = DropSlot.ItemID;
>    AActor* Owner = GetOwner();
>    UWorld* World = GetWorld();
>
>    if (Owner && World)
>    {
>        const FItemData* DropData = GetItemData(DroppedItemID);
>        if (!DropData || !DropData->PickupActorClass)
>        {
>            UE_LOG(LogTemp, Warning, TEXT("DropItemAt: %s 没有配>置 PickupActorClass"), *DroppedItemID.ToString());
>            return false;
>        }
>
>        FVector SpawnLocation = Owner->GetActorLocation()
>            + Owner->GetActorForwardVector() * DropDistance
>            + FVector(0.0f, 0.0f, DropHeight);
>
>        FRotator SpawnRotation = Owner->GetActorRotation();
>
>        FActorSpawnParameters SpawnParams;
>        SpawnParams.Owner = Owner;
>        SpawnParams.Instigator = Cast<APawn>(Owner);
>        SpawnParams.SpawnCollisionHandlingOverride = >ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButA>lwaysSpawn;
>
>        AActor* SpawnedActor = World->SpawnActor<AActor>>(DropData->PickupActorClass, SpawnLocation, >SpawnRotation, SpawnParams);
>        if (APickupItem* DroppedItem = Cast<APickupItem>>(SpawnedActor))
>        {
>            DroppedItem->ItemID = DroppedItemID;
>            DroppedItem->bRespawnable = false;
>            DroppedItem->RespawnTime = 0.0f;
>            DroppedItem->SetActive(true);
>        }
>    }
>
>    DropSlot.Count--;
>    if (DropSlot.Count <= 0)
>    {
>        DropSlot.ItemID = NAME_None;
>        DropSlot.Count = 0;
>    }
>
>    OnItemUsed.Broadcast(SlotIndex, DroppedItemID);
>    return true;
>}
>```

也算完成蛮多的，但是大部分时间浪费在了重构上（今天蓝图资产坏了，重构搞了半天，最后还是回溯才完成，以后要即使github，太重要了，还好有github记录版本可以回溯。）

明天开始实现recips。