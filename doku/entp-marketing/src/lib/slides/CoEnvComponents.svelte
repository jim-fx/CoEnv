<script lang="ts">
	import { Logo } from '$lib/elements';
	import { scale, fade } from 'svelte/transition';

	export let step;

	export let title;

	const opacity = 0.6;

	const t = '%I What is CoEnv -';

	$: switch (step) {
		case 0:
			$title = t + ' RoomBoard';
			break;
		case 1:
			$title = t + ' Cube';
			break;
		case 2:
			$title = t + ' Sigils';
			break;
		case 3:
			$title = '';
			break;
	}
</script>

<div class="wrapper step-{step}">
	<div
		transition:scale
		class="circle"
		id="board"
		style="border-color: rgba(255, 255, 0, {opacity});"
	>
		RoomBoard
	</div>
	{#if step > 0}
		<div
			transition:scale
			class="circle"
			id="cube"
			style="border-color: rgba(255, 0, 0, {opacity});"
		>
			Cube
		</div>
	{/if}

	{#if step > 1}
		<div
			transition:scale
			class="circle"
			id="sigils"
			style="border-color: rgba(0, 0, 255, {opacity});"
		>
			Sigils
		</div>
	{/if}

	{#if step > 2}
		<div id="coenv" transition:fade>
			<Logo />
		</div>
	{/if}
</div>

<style lang="scss">
	.wrapper {
		width: 70vh;
		height: 70vh;
		position: relative;
	}

	.circle {
		position: absolute;
		border: solid 20px;
		box-sizing: border-box;
		background-color: rgba(0, 0, 0, 0.8);
		border-radius: 100%;
		height: 40vh;
		width: 40vh;
		text-align: center;
		color: white;
		font-weight: bolder;
		font-family: 'Space Mono';
		font-size: 2em;
		display: grid;
		justify-content: center;
		align-items: center;
		transition: transform 0.3s ease;
	}

	#sigils {
		color: white;
	}

	.step-0 #board {
		transform: translate(15vh, 15vh);
	}

	.step-1 {
		#board {
			transform: translateY(15vh);
		}
		#cube {
			transform: translate(30vh, 15vh);
		}
	}

	.step-2,
	.step-3 {
		#board {
			transform: translateY(30vh);
		}
		#cube {
			transform: translate(30vh, 30vh);
		}
		#sigils {
			transform: translateX(15vh);
		}
	}

	#coenv {
		width: 40vh;
		height: 40vh;
		transform: translate(15vh, 16.5vh) scale(0.5);
		transform-origin: center center;
	}

	.step-3 {
	}
</style>
