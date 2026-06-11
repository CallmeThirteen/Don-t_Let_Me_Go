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
